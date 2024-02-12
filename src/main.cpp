#include <wx/cmdline.h>
#include <wx/textctrl.h>
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <iostream>
#include "MainFrameImpl.h"

class MyApp : public wxApp {
   public:
    virtual bool OnInit();
    bool parserCmdLine(wxString& file, wxString& config);
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    auto* frame = new MainFrameImpl(nullptr, wxID_ANY, "Logalizer");
    wxString file, config;
    parserCmdLine(file, config);
    frame->setCmdLineArgs(file, config);
    frame->Show(true);
    return true;
}

bool MyApp::parserCmdLine(wxString& file, wxString& config)
{
    static const wxCmdLineEntryDesc cmdLineDesc[] = {
        {wxCMD_LINE_SWITCH, "h", "help", "Displays this help", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
        {wxCMD_LINE_OPTION, "f", "file", "Input log file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
        {wxCMD_LINE_OPTION, "c", "config", "Configuration", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
        {wxCMD_LINE_NONE}};

    wxCmdLineParser parser(cmdLineDesc, argc, argv);
    parser.SetSwitchChars("-");
    parser.Parse();
    parser.Found("f", &file);
    parser.Found("c", &config);
    return true;
}
