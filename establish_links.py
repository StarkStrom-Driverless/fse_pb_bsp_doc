#!/usr/bin/env python3
import re
import sys

def convert_markdown_links(content):
    """
    Konvertiert Markdown-Links von relativen Pfaden zu Ankern.
    Beispiel: [Text](../docu/pin_definition.md) -> [Text](#pin-definition)
    
    Unterstriche (_) werden zu Bindestrichen (-) umgewandelt.
    """
    # Regex-Pattern für Markdown-Links: [Text](Pfad)
    pattern = r'\[([^\]]+)\]\(([^)]+\.md)\)'
    
    def replace_link(match):
        link_text = match.group(1)
        file_path = match.group(2)
        
        # Extrahiere Dateinamen ohne Erweiterung
        filename = file_path.split('/')[-1]
        anchor_name = filename.replace('.md', '')
        
        # Ersetze Unterstriche durch Bindestriche
        anchor_name = anchor_name.replace('_', '-')
        
        # Konvertiere zu Kleinbuchstaben für Anker
        anchor_name = anchor_name.lower()
        
        # Erstelle den neuen Link
        return f'[{link_text}](#{anchor_name})'
    
    # Ersetze alle Vorkommen
    converted = re.sub(pattern, replace_link, content)
    return converted

def main():
    if len(sys.argv) > 1:
        # Datei einlesen
        input_file = sys.argv[1]
        try:
            with open(input_file, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # Konvertieren
            converted = convert_markdown_links(content)
            
            # Ausgabe (optional in Datei schreiben)
            if len(sys.argv) > 2:
                output_file = sys.argv[2]
                with open(output_file, 'w', encoding='utf-8') as f:
                    f.write(converted)
                print(f"Konvertiert: {input_file} -> {output_file}")
            else:
                print(converted)
                
        except FileNotFoundError:
            print(f"Fehler: Datei '{input_file}' nicht gefunden")
            sys.exit(1)
    else:
        # Interaktiver Modus oder Beispiel
        test_input = "- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)"
        print("Eingabe:")
        print(test_input)
        print("\nAusgabe:")
        print(convert_markdown_links(test_input))

if __name__ == "__main__":
    main()
