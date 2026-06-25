# u3-applay-normalize-cpp.py
# generator   gemini google
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.
# Напиши на питоне функцию, которая принимает в качестве аргумента начальный путь к файлам. 
# Для каждого файла рекурсивно, вызови clang-format, передавая в качестве аргумента путь к файлу.

import re
import os
import subprocess

def format_files_recursive(start_path):
    """
    Рекурсивно ищет файлы C/C++/ObjC 
    """
    # Расширения файлов, которые обычно форматирует
    extensions = ('.cpp', '.c', '.h', '.hpp', '.cc', '.cxx', '.m', '.mm')
    
    # Проверяем, существует ли путь
    if not os.path.exists(start_path):
        print(f"Путь не найден: {start_path}")
        return

    def replacement(match):
        word = match.group(0)
        # Условие:
        # word[0] == '_' (есть ведущее подчеркивание)
        # word[1] не '_' (следующий не подчеркивание)
        # word[1] не заглавная буква (not word[1].isupper())
        # word[1] не число (not word[1].isupper())
        # _mm256 _mm512 _mm1024 _m128 _m256 _m1024 _mm_
        
        if len(word) > 4 and word[1] == 'm' and word[2] == 'm' and (word[3].isdigit() or word[3] == '_'):
            return word # Оставляем как есть
        
        if len(word) > 3 and word[1] == 'm' and word[2].isdigit():
            return word # Оставляем как есть
        
        if len(word) > 1 and word[1] != '_' and not word[1].isupper() and not word[1].isdigit():
            return word[1:]  # Удаляем первый символ
        return word  # Оставляем как есть

    # os.walk рекурсивно обходит директории
    for root, dirs, files in os.walk(start_path):
        for file in files:
            if file.endswith(extensions):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, 'r', encoding='cp1251', errors='replace') as f:
                        content = f.read()

                    # 2. Регулярное выражение:
                    # \b      - граница слова
                    # _       - один символ подчеркивания
                    # (?![_]) - Negative Lookahead: следующий символ НЕ подчеркивание
                    # (\w+)   - захватываем само слово
                    #pattern = r'\b_([^_]\w*)\b'
        
                    # Заменяем "_word" на "word"
                    #new_content = re.sub(pattern, r'\1', content)
                    new_content = re.sub(r'\b_\w+', replacement, content)

                    # 3. Записываем обработанный контент обратно
                    with open(file_path, 'w', encoding='cp1251', errors='replace') as f:
                        f.write(new_content)

                    print(f"Отформатирован: {file_path}")
                except subprocess.CalledProcessError as e:
                    print(f"Ошибка при форматировании {file_path}: {e}")


# --- Пример использования ---
if __name__ == "__main__":
    # Укажите путь к папке с вашими файлами
    target_folder = "./../../libs" 
    format_files_recursive(target_folder)
    #print("Раскомментируйте строку выше, чтобы запустить.")
