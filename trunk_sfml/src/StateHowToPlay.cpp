#include "StateHowToPlay.h"
#include "i18n.h"
#include "ResourceManager.h"

void formatText(sf::String &Text, int Width, int Height, bool BackLine = true)
{
    // Get the original string
    std::wstring String = Text.GetText();

    // Get the font
    const sf::Font &Font = Text.GetFont();

    // Get the font's size
    unsigned int CharSize = Text.GetSize();

    // Number of max lines
    const int NbLinesMax = Height/CharSize;

    // Line length counter
    int LineLength = 0;

    // Line counter
    int NbLines = 0;

    int totalSize = String.size();
    // For each character
    for( int k = 0; k < totalSize; k++ ) {

        // If there's a line break
        if ( String[k] == '\n' ) {

            // Increase the number of lines
            NbLines++;

            // Reset the width counter
            LineLength = 0;

            // If the number of max lines have been reached, discard the rest of the string
            if( NbLines > NbLinesMax ) {
                String.erase(String.begin()+k, String.end());
                break;
            }
        }

        // For any other character
        else {

            // Get the width of the single character
            LineLength += sf::String(std::wstring(1, String[k]), Font, CharSize).GetRect().GetWidth();

            // If the length is longer than the text's width
            if( LineLength > Width ) {
                
                if( !BackLine ) {

                    // From the current character
                    int i = k;
                    while( 1 ) {                        
                        if( String[i] == '\n' ) {
                            String.erase(String.begin()+k, String.begin()+k+1);
                            k--;
                            break;
                        }
                        i++;
                    }
                }
                else {
                    int i = 1;
                    while( 1 ) {
                        if( String[k-i] == ' ' ) {
                            String[k-i] = '\n';
                            k = k - i - 1;
                            break;
                        }
                        if( String[k-i] == '\n' or k == i ) {
                            String.insert(String.begin()+k, '\n');
                            k--;
                            break;
                        }
                        i++;
                    }
                }
            }
        }
    }
    Text.SetText(String);
}


StateHowToPlay::StateHowToPlay(){
    lDEBUG << Log::CON("StateHowToPlay");
}

StateHowToPlay::~StateHowToPlay(){
    lDEBUG << Log::DES("StateHowToPlay");
}

void StateHowToPlay::loadResources(){
    bodyText = L"";
    bodyText += _("The objective of the game is to swap one gem with an adjacent gem to form a horizontal or vertical chain of three or more gems.");
    bodyText += L"\n\n";
    bodyText += _("Click the first gem and then click the gem you want to swap it with. If the movement is correct, they will swap and the chained gems will disappear.");
    bodyText += L"\n\n";
    bodyText += _("Bonus points are given when more than three identical gems are formed. Sometimes chain reactions, called cascades, are triggered, where chains are formed by the falling gems. Cascades are awarded with bonus points.");

    spBackground.SetImage(ResMgr -> getImage("media/howtoScreen.png"));

    strTitle = sf::String(_("How to play"), 
                          ResMgr -> getFont("media/fuenteMenu.ttf", 48), 48);
    strTitle.SetX(300 + 470 / 2 - strTitle.GetRect().GetWidth() / 2);
    strTitle.SetY(20);

    strTitleShadow = strTitle;
    strTitleShadow.SetColor (sf::Color(0,0,0,125));
    strTitleShadow.Move(0, 2);

    strExitMessage = sf::String(_("Press escape to come back"), 
                                ResMgr -> getFont("media/fuenteMenu.ttf", 23), 23);
    strExitMessage.SetPosition(40, 550);

    strExitMessageShadow = strExitMessage;
    strExitMessageShadow.SetColor (sf::Color(0,0,0,125));
    strExitMessageShadow.Move(0, 2);

    strBodyText = sf::String(bodyText, ResMgr -> getFont("media/fNormal.ttf", 56),28);
    formatText(strBodyText, 450, 1000);
    strBodyText.SetPosition(310, 110);
}

void StateHowToPlay::event(sf::Event theEvent){
    if (theEvent.Type == sf::Event::KeyPressed and theEvent.Key.Code == sf::Key::Escape){
        pManager -> popState();
    }
}

void StateHowToPlay::update(bool isCovered){

}

void StateHowToPlay::draw(bool isCovered, DrawingQueue& queue){
    queue.Draw(0, spBackground);
    queue.Draw(1, strBodyText);
    queue.Draw(1, strTitle);
    queue.Draw(1, strExitMessage);

    queue.Draw(0.9, strTitleShadow);
    queue.Draw(0.9, strExitMessageShadow);
}
