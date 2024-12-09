package com.yamadalab.gitfarm.middleware.utils;

import java.io.File;


class Utils {

    companion object {
        private const val RESOURCE_PATH: String = "src/main/resources/libs";

        fun loadSharedLibrary(fileName: String) {
            val cppLibName: String = System.mapLibraryName(fileName);
            val cppLibFile: File = File("$RESOURCE_PATH/$cppLibName");
            println("cppLibFile : ${cppLibFile.absolutePath}");
            System.load(cppLibFile.absolutePath);
        }
    }
}