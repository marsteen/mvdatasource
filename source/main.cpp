#include <CFileIO.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        CFileIO fio;
        int error = 0;
        std::string nspace;
        std::string version;
        std::string postfix;
        //cout << "argc=" << argc <<  endl;

        for (int i = 2; i < argc; i++)
        {
            string arg = argv[i];

            if (arg == "-namespace")
            {
                if (argc > i + 1)
                {
                    nspace = argv[i + 1];
                }
                else
                {
                    cout << "***** error: missing argument for -namespace" << endl;
                    error = 1;
                }
            }
            else
            if (arg == "-version")
            {
                if (argc > i + 1)
                {
                    version = argv[i + 1];
                }
                else
                {
                    cout << "***** error: missing argument for -version" << endl;
                    error = 1;
                }
            }
            else
            if (arg == "-postfix")
            {
                if (argc > i + 1)
                {
                    postfix = string("_") + argv[i + 1];
                }
                else
                {
                    cout << "***** error: missing argument for -postfix" << endl;
                    error = 1;
                }
            }
        }


        if (error == 0)
        {
            if (fio.OpenFileRead(argv[1], ios::binary))
            {
                ofstream fstr;

                char buff[256];

                strcpy(buff, argv[1]);



                char* pkt = strrchr(buff, '.');
                if (pkt != NULL)
                {
                    string ShaderName;
                    string ShaderFile;
                    char* slash = strrchr(buff, '/');
                    *pkt = 0;


                    if (slash != 0)
                    {
                        ShaderName = slash + 1;
                    }
                    else
                    {
                        ShaderName = buff;
                    }
                    ShaderFile = string(buff) + postfix + ".cpp";
                    cout << "ShaderName:" << ShaderName << endl;
                    cout << "ShaderFile:" << ShaderFile << endl;


                    fstr.open(ShaderFile.c_str());
                    if (fstr.good())
                    {
                        bool NotEndOfFile = true;
                        string s;

                        if (nspace.size() > 0)
                        {
                            fstr << "namespace " << nspace << endl;
                            fstr << "{" << endl;
                        }


                        fstr << "const char* " <<  ShaderName << " =" << endl;

                        if (version.size() > 0)
                        {
                            fstr << '"' << "#version " << version << "\\n" << '"';
                        }

                        while (NotEndOfFile)
                        {
                            NotEndOfFile = fio.ReadLine(&s);
                            std::string MaskedLine = NStringTool::Mask(s, "\"");

                            fstr << '\n';
                            fstr << '"' << MaskedLine << "\\n" << '"';
                        }

                        fstr << ";" << endl;

                        if (nspace.size() > 0)
                        {
                            fstr << "}" << endl;
                        }
                    }
                    fstr.close();
                    fio.CloseFile();
                }
            }
            else
            {
                cout << "***** file error:" << argv[1] << endl;
            }
        }
    }
    else
    {
        cout << "mvdatasource <file.txt> [-namespace namespace] [-version version] [-prefix prefix]" << endl;
        cout << "Version 2.0" << endl;
    }

    return 0;
}
