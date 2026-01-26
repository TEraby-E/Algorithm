"""Test script to identify issues with cats.py"""

from cats import memo_diff, memo, autocorrect, minimum_mewtations, final_diff, furry_fixes
import sys

def test_memo_diff_decorator():
    """Test if memo_diff decorator is working correctly"""
    print("Testing memo_diff decorator...")
    
    # Check if minimum_mewtations is decorated with memo_diff
    # The decorator should be applied before the count wrapper
    func = minimum_mewtations
    print(f"minimum_mewtations function name: {func.__name__}")
    
    # Check if autocorrect is decorated with memo
    func2 = autocorrect
    print(f"autocorrect function name: {func2.__name__}")
    
    # Test memo_diff functionality
    @memo_diff
    def test_diff(a, b, limit):
        return len(a) + len(b)
    
    result1 = test_diff("abc", "def", 5)
    result2 = test_diff("abc", "def", 5)
    print(f"memo_diff test: {result1}, second call should be cached")
    
    return True

def test_final_diff_issues():
    """Test issues with final_diff function"""
    print("\nTesting final_diff issues...")
    
    # Check if final_diff is decorated with memo_diff
    # It should be, but currently it's not
    func = final_diff
    print(f"final_diff function name: {func.__name__}")
    
    # Test a simple case
    try:
        result = final_diff("cat", "cats", 5)
        print(f"final_diff('cat', 'cats', 5) = {result}")
    except Exception as e:
        print(f"Error in final_diff: {e}")
    
    # Test with keyboard distances
    from cats import KEY_DISTANCES
    print(f"KEY_DISTANCES type: {type(KEY_DISTANCES)}")
    if KEY_DISTANCES:
        sample_key = ('a', 's')
        print(f"KEY_DISTANCES[{sample_key}] = {KEY_DISTANCES.get(sample_key, 'Not found')}")
    
    return True

def test_autocorrect_memoization():
    """Test if autocorrect memoization is working"""
    print("\nTesting autocorrect memoization...")
    
    # Simple test
    word_list = ["hello", "world", "test"]
    
    # Define a simple diff function
    def simple_diff(w1, w2, limit):
        return abs(len(w1) - len(w2))
    
    # First call
    result1 = autocorrect("hell", word_list, simple_diff, 5)
    print(f"First autocorrect call: {result1}")
    
    # Second call with same parameters (should be cached)
    result2 = autocorrect("hell", word_list, simple_diff, 5)
    print(f"Second autocorrect call: {result2}")
    
    return True

def test_minimum_mewtations_wrapper():
    """Test the count wrapper issue"""
    print("\nTesting minimum_mewtations wrapper issue...")
    
    # The issue is: @memo_diff is applied, then count() wraps it
    # But count() might not preserve the memoization
    
    # Check if minimum_mewtations has call_count attribute (from count())
    if hasattr(minimum_mewtations, 'call_count'):
        print(f"minimum_mewtations.call_count exists: {minimum_mewtations.call_count}")
    else:
        print("minimum_mewtations.call_count does NOT exist - count() not applied?")
    
    # Reset call count
    if hasattr(minimum_mewtations, 'call_count'):
        minimum_mewtations.call_count = 0
        result = minimum_mewtations("cat", "cats", 10)
        print(f"minimum_mewtations('cat', 'cats', 10) = {result}, call_count = {minimum_mewtations.call_count}")
    
    return True

def main():
    print("=" * 60)
    print("Testing cats.py implementation issues")
    print("=" * 60)
    
    test_memo_diff_decorator()
    test_final_diff_issues()
    test_autocorrect_memoization()
    test_minimum_mewtations_wrapper()
    
    print("\n" + "=" * 60)
    print("Summary of issues found:")
    print("1. final_diff is not decorated with @memo_diff")
    print("2. final_diff uses get_key_distances() instead of KEY_DISTANCES")
    print("3. minimum_mewtations has @memo_diff but then count() wraps it")
    print("4. Need to check if count() preserves memoization")
    print("=" * 60)

if __name__ == "__main__":
    main()
