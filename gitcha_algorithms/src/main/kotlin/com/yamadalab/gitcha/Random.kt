package com.yamadalab.gitcha

import java.io.File
import java.io.FileNotFoundException

class Random {

    companion object {
        init {
            val cppLibPath: String = "src/main/cpp/build/lib";
            val cppLibName: String = System.mapLibraryName("gitcha_algorithms");
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

    external fun draw(items: Array<Pair<String, Pair<Double, Int>>>): String;
}