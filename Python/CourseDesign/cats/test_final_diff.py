"""Test final_diff function"""

from cats import final_diff

def test_final_diff():
    # Test 1: Identical strings
    assert final_diff("hello", "hello", 5) == 0
    print("Test 1 passed: identical strings")
    
    # Test 2: Case difference only (whole string)
    assert final_diff("Hello", "hello", 5) == 0
    print("Test 2 passed: case difference only (whole string)")
    
    # Test 3: Single character substitution
    # "cat" -> "bat": c->b substitution
    result = final_diff("cat", "bat", 5)
    print(f"Test 3: 'cat' -> 'bat' = {result}")
    
    # Test 4: Single character addition
    # "cat" -> "cats": add 's'
    result = final_diff("cat", "cats", 5)
    print(f"Test 4: 'cat' -> 'cats' = {result}")
    
    # Test 5: Single character deletion
    # "cats" -> "cat": delete 's'
    result = final_diff("cats", "cat", 5)
    print(f"Test 5: 'cats' -> 'cat' = {result}")
    
    # Test 6: Transposition (swap)
    # "form" -> "from": swap 'o' and 'r'
    result = final_diff("form", "from", 5)
    print(f"Test 6: 'form' -> 'from' = {result}")
    
    # Test 7: Case difference in middle
    # "Hello" -> "heLlo": L vs l
    result = final_diff("Hello", "heLlo", 5)
    print(f"Test 7: 'Hello' -> 'heLlo' = {result}")
    
    # Test 8: Exceed limit
    result = final_diff("abc", "xyz", 1)
    print(f"Test 8: 'abc' -> 'xyz' with limit 1 = {result}")
    
    # Test 9: Empty strings
    assert final_diff("", "", 5) == 0
    print("Test 9 passed: empty strings")
    
    # Test 10: One empty string
    result = final_diff("", "hello", 5)
    print(f"Test 10: '' -> 'hello' = {result}")

if __name__ == "__main__":
    test_final_diff()
