package com.yamadalab.gitfarm.middleware.algorithm.application;

import com.yamadalab.gitfarm.middleware.algorithm.domain.Item
import com.yamadalab.gitfarm.middleware.algorithm.domain.User
import com.yamadalab.gitfarm.middleware.utils.Utils
import java.io.FileNotFoundException

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

    private external fun nativeSetItems(items: Array<Pair<String, String>>): Boolean;
    private external fun nativeSetUser(user: User): Boolean;
    private external fun nativeDraw(): Item;

    public fun updateItems(items: Array<Item>): Boolean {
        val itemList: MutableList<Pair<String, String>> = mutableListOf();

        for (item in items) {
            val itemId: String = item.id;
            val itemGrade: String = item.grade.toString();

            val itemPair: Pair<String, String> = Pair<String, String>(itemId, itemGrade);

            itemList.add(itemPair);
        }

        val cItems: Array<Pair<String, String>> = itemList.toTypedArray();
        val isUpdated: Boolean = this.nativeSetItems(cItems);

        return isUpdated;
    }

    public fun setUser(user: User): Boolean {
        return this.nativeSetUser(user = user);
    }

    public fun draw(): Item {
        val drawItem: Item = this.nativeDraw();
        return drawItem;
    }
}