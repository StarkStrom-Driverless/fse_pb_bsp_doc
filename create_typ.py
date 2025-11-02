import re
import os
from pathlib import Path

def embed_markdown_recursively(content, base_path=".", visited=None, depth=0, max_depth=10):
    """
    Ersetzt Markdown-Links rekursiv durch den Inhalt der verlinkten Dateien.
    
    Args:
        content: Der Markdown-Inhalt als String
        base_path: Das Basisverzeichnis für relative Pfade
        visited: Set der bereits besuchten Dateien (verhindert Endlosschleifen)
        depth: Aktuelle Rekursionstiefe
        max_depth: Maximale Rekursionstiefe
    
    Returns:
        Verarbeiteter Markdown-Inhalt mit eingebetteten Dateien
    """
    if visited is None:
        visited = set()
    
    # Schutz gegen zu tiefe Rekursion
    if depth >= max_depth:
        print(f"Warnung: Maximale Rekursionstiefe ({max_depth}) erreicht")
        return content
    
    def replace_link(match):
        text = match.group(1)
        path = match.group(2)
        
        # Nur .md Dateien verarbeiten
        if not path.endswith('.md'):
            return match.group(0)
        
        # Vollständigen Pfad erstellen
        full_path = os.path.normpath(os.path.join(base_path, path))
        
        # Prüfen ob Datei existiert
        if not os.path.exists(full_path):
            print(f"Warnung: Datei nicht gefunden: {full_path}")
            return match.group(0)
        
        # Prüfen ob Datei bereits besucht wurde (verhindert Zyklen)
        abs_path = os.path.abspath(full_path)
        if abs_path in visited:
            print(f"Warnung: Zyklische Referenz erkannt: {full_path}")
            return match.group(0)
        
        # Datei zur visited-Liste hinzufügen
        visited.add(abs_path)
        
        # Datei lesen
        try:
            with open(full_path, 'r', encoding='utf-8') as f:
                file_content = f.read()
            
            # Neues Basisverzeichnis für rekursive Aufrufe
            new_base_path = os.path.dirname(full_path)
            
            # Rekursiv weitere Links in der eingefügten Datei ersetzen
            processed_content = embed_markdown_recursively(
                file_content, 
                new_base_path, 
                visited, 
                depth + 1, 
                max_depth
            )
            
            # Optional: Überschrift mit Original-Link-Text hinzufügen
            return f"\n\n## {text}\n\n{processed_content}\n\n"
            
        except Exception as e:
            print(f"Fehler beim Lesen von {full_path}: {e}")
            return match.group(0)
    
    # Regex für Markdown-Links: [text](path.md)
    pattern = r'\[([^\]]+)\]\(([^\)]+\.md)\)'
    processed = re.sub(pattern, replace_link, content)
    
    return processed


def process_markdown_file(input_file, output_file=None):
    """
    Verarbeitet eine Markdown-Datei und schreibt das Ergebnis.
    
    Args:
        input_file: Pfad zur Eingabedatei
        output_file: Pfad zur Ausgabedatei (optional, default: input_processed.md)
    """
    if output_file is None:
        base = os.path.splitext(input_file)[0]
        output_file = f"{base}_processed.md"
    
    # Basis-Pfad ist das Verzeichnis der Eingabedatei
    base_path = os.path.dirname(os.path.abspath(input_file))
    
    # Eingabedatei lesen
    with open(input_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Rekursiv verarbeiten
    processed = embed_markdown_recursively(content, base_path)
    
    # Ausgabedatei schreiben
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(processed)
    
    print(f"Verarbeitung abgeschlossen: {output_file}")


if __name__ == "__main__":
    # Verwendung
    process_markdown_file("README.md", "README_processed.md")
