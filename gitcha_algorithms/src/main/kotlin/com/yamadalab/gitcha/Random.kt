package com.yamadalab.gitcha

import java.io.File

class Random {

    companion object {
        init {
            val libraryPath = System.getProperty("java.library.path");
            println("java.library.path: $libraryPath");

            val lib: File = File("src/main/cpp/build/lib/" + System.mapLibraryName("gitcha_algorithms"));
            println("Library Path : ${lib.absolutePath}");
            System.load(lib.absolutePath);
        }
    }

    external fun wrsRandom(weights: LongArray): Int;
    external fun pityRandom(baseChance: Int, maxFails: Int, currentFails: Int): Boolean;
}