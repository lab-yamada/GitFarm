package com.yamadalab.gitfarm.middleware.application;

import java.io.File;
import java.io.FileNotFoundException;

class GitCurl {

    companion object {
        init {
            val userHome: String = System.getProperty("user.home");
            val cppLibPath: String = "$userHome/gitfarm_ws/gitfarm_middleware/src/main/c/build/lib";
            val cppLibName: String = System.mapLibraryName("gitfarm_middleware");
            val cppLibFullPath: String = "$cppLibPath/$cppLibName";

            try {
                val cppLibFile: File = File(cppLibFullPath);
                println("CPP Library Path : ${cppLibFile.absolutePath}");
                System.load(cppLibFile.absolutePath);
            } catch (usle: UnsatisfiedLinkError) {
                println("$usle");
            } catch (fne: FileNotFoundException) {
                println("$fne");
            }
        }
    }

    external fun nativePostRequest(url: String): String;
}