"""Test memoization issue in final_diff"""

from cats import final_diff

def test_memo_issue():
    # Test with same (i, j) but different limits
    # This should expose the memoization bug
    
    print("Testing memoization issue...")
    
    # Case 1: "ab" -> "cd" with limit 0
    # Should return 100 (exceeds limit)
    result1 = final_diff("ab", "cd", 0)
    print(f"'ab' -> 'cd' with limit 0: {result1}")
    
    # Case 2: "ab" -> "cd" with limit 1
    # Should also return 100 (needs 2 substitutions, limit is 1)
    result2 = final_diff("ab", "cd", 1)
    print(f"'ab' -> 'cd' with limit 1: {result2}")
    
    # Case 3: "ab" -> "cd" with limit 2
    # Should return 2 (2 substitutions)
    result3 = final_diff("ab", "cd", 2)
    print(f"'ab' -> 'cd' with limit 2: {result3}")
    
    # Case 4: "ab" -> "cd" with limit 3
    # Should return 2 (2 substitutions)
    result4 = final_diff("ab", "cd", 3)
    print(f"'ab' -> 'cd' with limit 3: {result4}")
    
    print("\nTesting with keyboard distances...")
    # Test keyboard distance
    # "a" -> "s" should have a small distance (they're close on keyboard)
    result5 = final_diff("a", "s", 5)
    print(f"'a' -> 's': {result5}")
    
    # "a" -> "l" should have a larger distance
    result6 = final_diff("a", "l", 5)
    print(f"'a' -> 'l': {result6}")
    
    # "q" -> "p" should have a large distance (far apart on keyboard)
    result7 = final_diff("q", "p", 5)
    print(f"'q' -> 'p': {result7}")

if __name__ == "__main__":
    test_memo_issue()
