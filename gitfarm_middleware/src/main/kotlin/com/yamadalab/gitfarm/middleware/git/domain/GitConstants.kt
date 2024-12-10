package com.yamadalab.gitfarm.middleware.git.domain

class GitConstants {

    companion object {
        public const val KTOR_HTTP_ACCEPT_TYPE: String = "application/vnd.github+json";
        public val KTOR_HTTP_USER_AGENT: Array<String> = arrayOf("User-Agent", "GitFarm/1.0.0");
        public const val GITHUB_GRAPHQL_API_URL: String = "https://api.github.com/graphql";
        public const val GITHUB_GRAPHQL_CONTRIBUTION_BY_YEAR_NAME: String = "contribution_by_year.graphql";
        public const val GITHUB_TOKEN_YAML_NAME: String = "user_token.yaml";
    }
}