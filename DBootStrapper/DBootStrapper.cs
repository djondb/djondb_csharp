using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;
using System.Configuration;

namespace Djondb
{
    public class DBootStrapper
    {
        private static string _x86Dir;
        private static string _x64Dir;

        public static void LoadLibrary()
        {
            _x86Dir = ConfigurationSettings.AppSettings["x86"];
            if (string.IsNullOrEmpty( _x86Dir))
            {
                _x86Dir = "x86";
            }
            _x64Dir = ConfigurationSettings.AppSettings["x64"];
            if (string.IsNullOrEmpty(_x64Dir))
            {
                _x64Dir = "x64";
            }

            AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(ResolverHandler);
        }

        private static System.Reflection.Assembly ResolverHandler(
           object sender, ResolveEventArgs args)
        {
            if (args.Name.StartsWith("djondb_csharp"))
            {
                String appDir = null;
                var webAssemblies = AppDomain.CurrentDomain.GetAssemblies()
                      .Where(a => a.FullName.StartsWith("System.Web"));
                foreach (var webAssembly in webAssemblies)
                {
                    var httpRuntimeType = webAssembly.GetType("System.Web.HttpRuntime");
                    if (httpRuntimeType != null)
                    {
                        PropertyInfo prop = httpRuntimeType.GetProperty("BinDirectory", BindingFlags.GetProperty | BindingFlags.Static | BindingFlags.Public);
                        appDir = (string)prop.GetValue(null, null);
                    }
                }
                if (appDir == null) 
                {
                    appDir = System.AppDomain.CurrentDomain.BaseDirectory;
                }
                //String appDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

                // Here we detect the type of CPU architecture 
                // at runtime and select the mixed-mode library 
                // from the corresponding directory.
                // This approach assumes that we only have two 
                // versions of the mixed mode assembly, 
                // X86 and X64, it will not work however on 
                // ARM-based applications or any other non X86/X64 
                // platforms
                String relativeDir =
                   String.Format("{0}\\djondb_csharp.dll",
                         (IntPtr.Size == 8) ? _x64Dir : _x86Dir);
                String libraryPath = Path.Combine(appDir, relativeDir);

                // we do not need this resolver anymore
                AppDomain.CurrentDomain.AssemblyResolve -= ResolverHandler;

                return Assembly.LoadFile(libraryPath);
            }
            return null;
        }

    }
}


