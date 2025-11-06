with open("swedish.txt", "r", encoding="utf-8") as file:
    lines = file.readlines()
five_letter_words = [line.strip() for line in lines if len(line.strip()) == 5]
with open("five_letter_words.txt", "w", encoding="utf-8") as file:
    for word in five_letter_words:
        file.write(word + "\n")
print(f"Filtered {len(five_letter_words)} words with exactly 5 letters.")
