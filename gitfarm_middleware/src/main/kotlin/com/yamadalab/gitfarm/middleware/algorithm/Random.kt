package com.yamadalab.gitfarm.middleware.algorithm;

import com.yamadalab.gitfarm.middleware.utils.Utils
import java.io.*

class Random {

    companion object {
        init {
            try {
                Utils.loadSharedLibrary("gitfarm_algorithm");
            } catch (usle: UnsatisfiedLinkError) {
                println("$usle");
            } catch (fne: FileNotFoundException) {
                println("$fne");
            }
        }
    }

    private external fun nativeSetItems(items: Array<Pair<String, Pair<Double, Int>>>): Unit;
    private external fun nativeDraw(): Item;

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
        this.nativeSetItems(citems);

        val drawItem: Item = this.nativeDraw();
        return drawItem.id;
    }
}