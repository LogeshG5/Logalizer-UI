#include "MainFrameImpl.h"
#include <wx/arrstr.h>
#include <wx/busyinfo.h>
#include <wx/dir.h>
#include <wx/textctrl.h>
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <array>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "platform/application.h"

namespace fs = std::filesystem;

MainFrameImpl::MainFrameImpl(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
                             const wxSize& size, long style)
    : MainFrame(parent, id, title, pos, size, style)
{
    loadProfiles();
    setupDragDrop();
}

MainFrameImpl::~MainFrameImpl()
{
}

void MainFrameImpl::setupDragDrop()
{
    m_dropText->DragAcceptFiles(true);
    m_dropText->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(MainFrameImpl::OnDropFiles), NULL, this);
}

void MainFrameImpl::loadProfiles()
{
    try {
        fs::path profile = getExeDir() / "config";
        for (const auto& entry : fs::directory_iterator(profile)) {
            if (entry.path().extension() == ".json") {
                std::string profile_name = entry.path().stem().string();
                m_profileCombo->Append(profile_name);
                profiles_[profile_name] = entry.path().string();
            }
        }
        m_profileCombo->Append("Browse...");
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    if (!m_profileCombo->IsListEmpty()) m_profileCombo->SetSelection(0);
}

void MainFrameImpl::onGenerate(wxCommandEvent& event)
{
    const std::string filePath = m_logFilePicker->GetPath().ToStdString();
    const std::string selectedProfile = m_profileCombo->GetStringSelection().ToStdString();
    const std::string profilePath = profiles_[selectedProfile];
    if (filePath.empty()) wxMessageBox(wxT("Choose input file"));
    executeCmd(filePath, profilePath);
}

int MainFrameImpl::execute(std::string cmd, std::string& output)
{
    const int bufsize = 128;
    std::array<char, bufsize> buffer;
    cmd += " 2>&1";

#ifdef _WIN32
    auto pipe = _popen(cmd.c_str(), "r");
#else
    auto pipe = popen(cmd.c_str(), "r");
#endif
    if (!pipe) throw std::runtime_error("popen() failed!");

    size_t count;
    do {
        if ((count = fread(buffer.data(), 1, bufsize, pipe)) > 0) {
            output.insert(output.end(), std::begin(buffer), std::next(std::begin(buffer), count));
        }
    } while (count > 0);

#ifdef _WIN32
    return _pclose(pipe);
#else
    return pclose(pipe);
#endif
}

void MainFrameImpl::executeCmd(const std::string& filePath, const std::string& profilePath)
{
    const std::string logalizerPath = getLogalizerPath().string();
    const std::string command = logalizerPath + " -f \"" + filePath + "\" -c \"" + profilePath + "\"";
    std::cout << command << std::endl;
    std::string output;
    if (const int returnval = execute(command, output)) {
        std::cerr << command << " execution failed with code " << returnval << "\n" << output << "\n";
        wxString message(output);
        wxMessageBox(message, wxT("Generation failed!"), wxOK | wxICON_ERROR);
    }
}

void MainFrameImpl::OnDropFiles(wxDropFilesEvent& event)
{
    if (event.GetNumberOfFiles() > 0) {
        wxString* dropped = event.GetFiles();
        wxASSERT(dropped);

        wxBusyCursor busyCursor;
        wxWindowDisabler disabler;
        wxBusyInfo busyInfo(_("Adding files, wait please..."));

        wxString name;
        wxArrayString files;

        for (int i = 0; i < event.GetNumberOfFiles(); i++) {
            name = dropped[i];
            if (wxFileExists(name))
                files.push_back(name);
            else if (wxDirExists(name))
                wxDir::GetAllFiles(name, &files);
        }

        wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
        wxASSERT(textCtrl);
        textCtrl->Clear();
        size_t filesToProcess = files.size() > 0 ? 1 : 0;  // process only one file
        for (size_t i = 0; i < filesToProcess; i++) {
            *textCtrl << files[i] << wxT('\n');
            m_logFilePicker->SetPath(files[i]);
        }
    }
}

void MainFrameImpl::onProfileSelected(wxCommandEvent& event)
{
    if (m_profileCombo->GetStringSelection() != "Browse...") return;

    wxFileDialog openFileDialog(this, _("Select config"), "", "", "config (*.json)|*.json",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;  // the user canceled...

    appendProfile(openFileDialog.GetPath());
}

void MainFrameImpl::onLogFileChanged(wxFileDirPickerEvent& event)
{
    m_dropText->SetValue(m_logFilePicker->GetPath());
}

void MainFrameImpl::setCmdLineArgs(const wxString& file, const wxString& profile)
{
    if (!file.IsEmpty()) {
        m_logFilePicker->SetPath(file);
        m_dropText->WriteText(file);
    }
    if (!profile.IsEmpty()) appendProfile(profile);
}

void MainFrameImpl::appendProfile(const wxString& file)
{
    std::string profile_name = fs::path(file.ToStdString()).stem().string();
    // check if it is already existing
    if (profiles_.find(profile_name) == profiles_.end()) {
        // does not exist
        // remove Browse... and add this at the end, add Browse... again
        m_profileCombo->Delete(m_profileCombo->GetCount() - 1);
        profiles_[profile_name] = file;
        m_profileCombo->Append(profile_name);
        m_profileCombo->Append("Browse...");
        m_profileCombo->SetSelection(m_profileCombo->GetCount() - 2);
    }
    else {
        // This profile already exist, update the path
        profiles_[profile_name] = file;
    }
}
