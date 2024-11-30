package com.yamadalab.gitfarm.domain

class Item {

    private var id: String = "";
    private var probability: Double = 0.0;
    private var failCount: Int = 0;

    constructor(id: String, probability: Double, failCount: Int) {
        this.id = id;
        this.probability = probability;
        this.failCount = failCount;
    }

    public fun getId(): String {
        return this.id;
    }

    public fun setId(id: String) {
        this.id = id;
    }

    public fun getProbability(): Double {
        return this.probability;
    }

    public fun setProbability(probability: Double) {
        this.probability = probability;
    }

    public fun getFailCount(): Int {
        return this.failCount;
    }

    public fun setFailCount(failCount: Int) {
        this.failCount = failCount;
    }
}