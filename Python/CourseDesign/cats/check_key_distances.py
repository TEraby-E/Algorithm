"""Check KEY_DISTANCES values"""

from cats import KEY_DISTANCES

def check_distances():
    print("Checking KEY_DISTANCES...")
    
    # Check some specific distances
    pairs = [
        ("a", "a"),
        ("a", "s"),
        ("a", "d"),
        ("a", "l"),
        ("q", "p"),
        ("a", "c"),
        ("c", "b"),
        ("f", "r"),
        ("o", "r"),
        ("r", "o"),
    ]
    
    for pair in pairs:
        key = (pair[0], pair[1])
        if key in KEY_DISTANCES:
            print(f"KEY_DISTANCES[{pair[0]}, {pair[1]}] = {KEY_DISTANCES[key]}")
            print(f"  Rounded: {round(KEY_DISTANCES[key])}")
        else:
            print(f"KEY_DISTANCES[{pair[0]}, {pair[1]}] not found")
    
    # Check if distances are symmetric
    print("\nChecking symmetry...")
    for pair in pairs:
        key1 = (pair[0], pair[1])
        key2 = (pair[1], pair[0])
        if key1 in KEY_DISTANCES and key2 in KEY_DISTANCES:
            if KEY_DISTANCES[key1] != KEY_DISTANCES[key2]:
                print(f"Asymmetric: {key1}={KEY_DISTANCES[key1]}, {key2}={KEY_DISTANCES[key2]}")
            else:
                print(f"Symmetric: {key1}={KEY_DISTANCES[key1]}")
        else:
            print(f"One or both keys not found: {key1}, {key2}")

if __name__ == "__main__":
    check_distances()
