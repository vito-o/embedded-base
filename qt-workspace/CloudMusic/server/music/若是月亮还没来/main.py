# 读取歌词文件
with open('lyric.txt', 'r', encoding='utf-8') as file:
    lyrics = file.readlines()

# 将每一行后面的换行符替换为 \r\n
with open('updated_lyrics.txt', 'w', encoding='utf-8', newline='') as file:
    for line in lyrics:
        file.write(line.rstrip('\n') + '\r\n')