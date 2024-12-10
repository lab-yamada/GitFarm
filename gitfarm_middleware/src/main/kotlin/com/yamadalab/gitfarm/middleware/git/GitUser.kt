package com.yamadalab.gitfarm.middleware.git;

import kotlinx.serialization.Serializable;

@Serializable
data class GitUser(
    val data: UserData
)

@Serializable
data class UserData(
    val user: UserContributions
)

@Serializable
data class UserContributions(
    val contributionsCollection: ContributionCalendar
)

@Serializable
data class ContributionCalendar(
    val contributionCalendar: Contributions
)

@Serializable
data class Contributions(
    val totalContributions: Int
)