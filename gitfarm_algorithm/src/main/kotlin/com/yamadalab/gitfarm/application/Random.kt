package com.yamadalab.gitfarm.application;

import com.yamadalab.gitfarm.domain.Item;
import java.io.File;
import java.io.FileNotFoundException;

class Random {

    companion object {
        init {
            val userHome: String = System.getProperty("user.home");
            val cppLibPath: String = "$userHome/gitfarm_ws/gitfarm_algorithm/src/main/cpp/build/lib";
            val cppLibName: String = System.mapLibraryName("gitfarm_algorithm");
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

    private external fun cSetItems(items: Array<Pair<String, Pair<Double, Int>>>): Unit;
    private external fun cDraw(): Item;

    public fun draw(items: Array<Item>): String {
        val itemList: MutableList<Pair<String, Pair<Double, Int>>> = mutableListOf();

        for (item in items) {
            val itemId: String = item.id;
            val itemProbability: Double = item.probability;
            val itemFailCount: Int = item.failCount;

            val itemInfoPair: Pair<Double, Int> = Pair<Double, Int>(itemProbability, itemFailCount);
            val itemPair: Pair<String, Pair<Double, Int>> = Pair<String, Pair<Double, Int>>(itemId, itemInfoPair);

            itemList.add(itemPair);
        }

        val citems: Array<Pair<String, Pair<Double, Int>>> = itemList.toTypedArray();
        this.cSetItems(citems);

        val drawItem: Item = this.cDraw();
        return drawItem.id;
    }
}
