#include "Util.h"
#include "log.h"

// template <typename value_type>
// std::string to_string ( const value_type & obj )
// {
//     std::ostringstream os;
//     os << std::fixed;
//     os << obj;

//     return os.str();
// }

std::vector<std::wstring> tokenize (const std::wstring & text, const wchar_t sep = L'\n'){
    std::vector<std::wstring> tokens;	

    std::wstring::size_type lastPos = text.find_first_not_of(sep, 0);

    // Find first "non-delimiter".
    std::wstring::size_type pos = text.find_first_of(sep, lastPos);
		
    tokens.clear();
    while (std::wstring::npos != pos || std::wstring::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(text.substr(lastPos, pos - lastPos));

        // Skip '\n'.  Note the "not_of"
        lastPos = text.find_first_not_of(sep, pos);

        // Find next "non-delimiter"
        pos = text.find_first_of(sep, lastPos);
    }	

    return tokens;
}

std::vector<sf::String> formatText(std::wstring &bodyText, const sf::Font& font, 
                                   int width)
{
    // Get the font's size
    unsigned int charSize = font.GetCharacterSize();

    // First division (line breaks)
    std::vector<std::wstring> firstDivision = tokenize(bodyText);

    // We divide the original text in words
    std::vector<std::wstring> singleWords = tokenize(bodyText, L' ');
    
    // Number of words found
    size_t totalWords = singleWords.size();
    
    // Lines to be created
    std::vector<sf::String> lines;

    // Placeholder for the current line
    std::wstring currentLine;

    // Current line's width
    float currentLineWidth = 0;

    // Iterate over all the single words
    for (size_t w = 0; w < totalWords; ++w){

        // If the current word is a linebreak
        if (singleWords[w] == L"\n"){

            // Add the previous line to the vector
            lines.push_back(sf::String(currentLine, font, charSize));

            // Reset the line
            currentLine = L"";
            currentLineWidth = 0;
        }else{

            // Get the current word's width
            float currentWordWidth = sf::String(singleWords[w] + L" ", font, charSize).GetRect().GetWidth();

            // If the line + word are longer than max width
            if (currentLineWidth + currentWordWidth > width){

                // Add previous line to the vector
                lines.push_back(sf::String(currentLine, font, charSize));

                // Restart the line with this word
                currentLine = singleWords[w];
                currentLineWidth = currentWordWidth;
            }else{

                // Update the current line
                if (currentLine != L""){
                    currentLine += L" ";
                }
                currentLine += singleWords[w];
                currentLineWidth += currentWordWidth;
            }
        }
    }

    // Add remaining words to the vector
    lines.push_back(sf::String(currentLine, font, charSize));

    return lines;
}
