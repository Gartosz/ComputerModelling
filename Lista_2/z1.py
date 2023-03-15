from re import sub

if __name__ == "__main__":
    words_dict = {}
    with open("test_file.txt", "r") as file:
        words = file.read().split()
        words = [sub(r'\W+', '', word.lower()) for word in words]
        words_dict = {word: words.count(word) for word in set(words)}
    words_dict = dict(sorted(words_dict.items(), reverse=True, key=lambda item: item[1]))
    words_ranks = {rank + 1: (word, words_dict[word]) for rank, word in enumerate(words_dict.keys())}
    print(words_ranks)