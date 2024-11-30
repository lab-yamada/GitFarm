package com.yamadalab.gitcha.application;

import com.yamadalab.gitcha.domain.Item;
import java.io.File;
import java.io.FileNotFoundException;

class Random {

    companion object {
        init {
            val userHome: String = System.getProperty("user.home");
            val cppLibPath: String = "$userHome/gitcha_ws/gitcha_algorithms/src/main/cpp/build/lib";
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

    private external fun wrsDraw(): Item;
    private external fun cdraw(items: Array<Pair<String, Pair<Double, Int>>>): String;

    public fun draw(items: Array<Item>): String {
        val itemList: MutableList<Pair<String, Pair<Double, Int>>> = mutableListOf();

        for (item in items) {
            val itemId: String = item.getId();
            val itemProbability: Double = item.getProbability();
            val itemFailCount: Int = item.getFailCount();

            val itemInfoPair: Pair<Double, Int> = Pair<Double, Int>(itemProbability, itemFailCount);
            val itemPair: Pair<String, Pair<Double, Int>> = Pair<String, Pair<Double, Int>>(itemId, itemInfoPair);

            itemList.add(itemPair);
        }

        val citems: Array<Pair<String, Pair<Double, Int>>> = itemList.toTypedArray();
        println("Draw, citems : ${citems.size}");

        val drawItemId: String = cdraw(items = citems);
        return drawItemId;
    }
}