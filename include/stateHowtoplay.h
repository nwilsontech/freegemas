#ifndef _STATEHOWTOPLAY_H_
#define _STATEHOWTOPLAY_H_

#include <Gosu/Gosu.hpp>
#include "state.h"

#include <boost/shared_ptr.hpp>

class SDLFont;
class SDLText;
class Game;

class StateHowtoplay : public State{
public:

    StateHowtoplay(Game * p);
    void update();
    void draw();
    void buttonDown(Gosu::Button B);

    ~StateHowtoplay();

private:
    boost::shared_ptr<Gosu::Image> imgBackground;

    boost::shared_ptr<SDLFont> fontTitle, fontSubtitle;
    boost::shared_ptr<SDLText> fontBodyText;

    wstring bodyText;
    vector<wstring> preparedText;
    boost::shared_ptr<Gosu::Image> imgBodyText;

};

#endif /* _STATEHOWTOPLAY_H_ */