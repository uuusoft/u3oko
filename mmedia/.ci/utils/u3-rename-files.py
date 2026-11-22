# u3-rename-files.py
# ai-generator  google gemini 
# author        Erashov Anton erashov2026@proton.me
# date          30.07.2026
# copyright     Erashov A.I.
# ai-prompt
# Напиши на питоне функцию, которая принимает в качестве аргумента начальный путь к каталогу и рекурсивно меняет имена всех файлов, который совпадают с указанным.

import os

def rename_files_recursive(root_dir: str, target_name: str, new_name: str):
    # os.walk автоматически обходит все вложенные папки
    for dirpath, dirnames, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename == target_name:
                old_file_path = os.path.join(dirpath, filename)
                new_file_path = os.path.join(dirpath, new_name)
                
                try:
                    os.rename(old_file_path, new_file_path)
                except OSError as e:
                    print(file=f"Ошибка при переименовании {old_file_path}: {e}")


# --- Пример использования ---
if __name__ == "__main__":
    # Укажите путь к папке с вашими файлами
    target_folder = "./../../" 
    rename_files_recursive(target_folder, 'U3_COMMERCIAL_PART.info', 'u3-folder-with-commercial-part.mark')
    