#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/similarity.h"

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d - Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
            exit(1); \
        } \
    } while(0)

#define ASSERT_DOUBLE_EQ(expected, actual, tolerance) \
    do { \
        double diff = (expected) - (actual); \
        if (diff < 0) diff = -diff; \
        if (diff > (tolerance)) { \
            printf("FAIL: %s:%d - Expected %.3f, got %.3f (diff: %.3f)\n", __FILE__, __LINE__, (expected), (actual), diff); \
            exit(1); \
        } \
    } while(0)

void test_levenshtein_distance() {
    printf("Testing Levenshtein distance...\n");
    
    // Basic tests
    ASSERT_EQ(0, levenshtein_distance("", ""));
    ASSERT_EQ(3, levenshtein_distance("", "abc"));
    ASSERT_EQ(3, levenshtein_distance("abc", ""));
    ASSERT_EQ(0, levenshtein_distance("abc", "abc"));
    
    // Single character differences
    ASSERT_EQ(1, levenshtein_distance("abc", "ab"));   // deletion
    ASSERT_EQ(1, levenshtein_distance("ab", "abc"));   // insertion
    ASSERT_EQ(1, levenshtein_distance("abc", "axc"));  // substitution
    
    // Complex examples
    ASSERT_EQ(1, levenshtein_distance("pwd", "pwdd"));
    ASSERT_EQ(1, levenshtein_distance("ls", "lss"));
    ASSERT_EQ(3, levenshtein_distance("kitten", "sitting"));
    ASSERT_EQ(1, levenshtein_distance("cat", "bat"));
    
    printf("Levenshtein distance tests passed!\n");
}

void test_damerau_levenshtein_distance() {
    printf("Testing Damerau-Levenshtein distance...\n");
    
    // Basic tests (same as Levenshtein for these cases)
    ASSERT_EQ(0, damerau_levenshtein_distance("", ""));
    ASSERT_EQ(0, damerau_levenshtein_distance("abc", "abc"));
    
    // Transposition tests
    ASSERT_EQ(1, damerau_levenshtein_distance("ab", "ba"));
    ASSERT_EQ(1, damerau_levenshtein_distance("abc", "acb"));
    ASSERT_EQ(1, damerau_levenshtein_distance("ca", "ac"));
    
    // Should be same or better than regular Levenshtein
    int lev = levenshtein_distance("pwd", "pwdd");
    int dlev = damerau_levenshtein_distance("pwd", "pwdd");
    assert(dlev <= lev);
    
    printf("Damerau-Levenshtein distance tests passed!\n");
}

void test_jaro_winkler_similarity() {
    printf("Testing Jaro-Winkler similarity...\n");
    
    // Exact matches
    ASSERT_DOUBLE_EQ(1.0, jaro_winkler_similarity("", ""), 0.001);
    ASSERT_DOUBLE_EQ(1.0, jaro_winkler_similarity("abc", "abc"), 0.001);
    
    // No matches
    ASSERT_DOUBLE_EQ(0.0, jaro_winkler_similarity("abc", "def"), 0.001);
    
    // Partial matches (should be between 0 and 1)
    double sim = jaro_winkler_similarity("pwd", "pwdd");
    assert(sim > 0.0 && sim < 1.0);
    
    // Prefix bonus test
    double sim1 = jaro_winkler_similarity("prefix_test", "prefix_other");
    double sim2 = jaro_winkler_similarity("test_prefix", "other_prefix");
    assert(sim1 > sim2); // First should have higher score due to common prefix
    
    printf("Jaro-Winkler similarity tests passed!\n");
}

void test_soundex() {
    printf("Testing Soundex...\n");
    
    char code[5];
    
    // Basic soundex tests
    soundex("", code);
    assert(code[0] == '0');
    
    soundex("Robert", code);
    assert(strcmp(code, "R163") == 0);
    
    soundex("Rupert", code);
    assert(strcmp(code, "R163") == 0);
    
    soundex("Rubin", code);
    assert(strcmp(code, "R150") == 0);
    
    // Similarity tests
    assert(soundex_similarity("Robert", "Rupert") == 1);
    assert(soundex_similarity("Robert", "Rubin") == 0);
    
    printf("Soundex tests passed!\n");
}

void test_ngram_similarity() {
    printf("Testing N-gram similarity...\n");
    
    // Exact matches
    ASSERT_DOUBLE_EQ(1.0, ngram_similarity("abc", "abc", 2), 0.001);
    
    // No matches
    ASSERT_DOUBLE_EQ(0.0, ngram_similarity("abc", "def", 2), 0.001);
    
    // Partial matches
    double sim = ngram_similarity("abcd", "abef", 2);
    assert(sim > 0.0 && sim < 1.0);
    
    // Different n values
    double sim2 = ngram_similarity("abcdef", "abcxyz", 2);
    double sim3 = ngram_similarity("abcdef", "abcxyz", 3);
    assert(sim2 > 0.0 && sim3 > 0.0);
    
    printf("N-gram similarity tests passed!\n");
}

void test_lcs_similarity() {
    printf("Testing LCS similarity...\n");
    
    // Exact matches
    ASSERT_DOUBLE_EQ(1.0, lcs_similarity("", ""), 0.001);
    ASSERT_DOUBLE_EQ(1.0, lcs_similarity("abc", "abc"), 0.001);
    
    // No common subsequence
    ASSERT_DOUBLE_EQ(0.0, lcs_similarity("abc", "def"), 0.001);
    
    // Partial matches
    double sim = lcs_similarity("abcd", "axcd");
    assert(sim > 0.0 && sim < 1.0);
    
    // LCS length tests
    ASSERT_EQ(0, lcs_length("", ""));
    ASSERT_EQ(0, lcs_length("abc", "def"));
    ASSERT_EQ(3, lcs_length("abc", "abc"));
    ASSERT_EQ(2, lcs_length("abc", "axc"));
    
    printf("LCS similarity tests passed!\n");
}

void test_calculate_similarity_score() {
    printf("Testing hybrid similarity score...\n");
    
    // Exact match should give perfect score
    ASSERT_DOUBLE_EQ(1.0, calculate_similarity_score("pwd", "pwd"), 0.001);
    
    // Different cases should be handled
    ASSERT_DOUBLE_EQ(1.0, calculate_similarity_score("PWD", "pwd"), 0.001);
    
    // Similar commands should have high scores
    double score = calculate_similarity_score("pwd", "pwdd");
    assert(score > 0.7);
    
    // Very different commands should have low scores
    double low_score = calculate_similarity_score("pwd", "xyzabc");
    assert(low_score < 0.3);
    
    // Prefix matching should boost score
    double prefix_score = calculate_similarity_score("pre", "prefix");
    double no_prefix_score = calculate_similarity_score("fix", "prefix");
    assert(prefix_score > no_prefix_score);
    
    printf("Hybrid similarity score tests passed!\n");
}

int main() {
    printf("Running similarity algorithm tests...\n\n");
    
    test_levenshtein_distance();
    test_damerau_levenshtein_distance();
    test_jaro_winkler_similarity();
    test_soundex();
    test_ngram_similarity();
    test_lcs_similarity();
    test_calculate_similarity_score();
    
    printf("\nAll similarity tests passed! ✓\n");
    return 0;
}