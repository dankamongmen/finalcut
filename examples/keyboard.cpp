/***********************************************************************
* keyboard.cpp - Shows typed-in key name                               *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2015-2019 Markus Gans                                      *
*                                                                      *
* The Final Cut is free software; you can redistribute it and/or       *
* modify it under the terms of the GNU Lesser General Public License   *
* as published by the Free Software Foundation; either version 3 of    *
* the License, or (at your option) any later version.                  *
*                                                                      *
* The Final Cut is distributed in the hope that it will be useful,     *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

#include <final/final.h>

//----------------------------------------------------------------------
// class Keyboard
//----------------------------------------------------------------------

class Keyboard : public finalcut::FWidget
{
  public:
    // Constructor
    explicit Keyboard (finalcut::FWidget* = nullptr);

  protected:
    // Event handlers
    void onKeyPress (finalcut::FKeyEvent*) override;
    void onAccel (finalcut::FAccelEvent*) override;

  private:
    // Methods
    void draw() override;
};

//----------------------------------------------------------------------
Keyboard::Keyboard (finalcut::FWidget* parent)
  : finalcut::FWidget(parent)
{
  setFWidgetColors().term_fg = finalcut::fc::Default;
  setFWidgetColors().term_bg = finalcut::fc::Default;
}

//----------------------------------------------------------------------
void Keyboard::onKeyPress (finalcut::FKeyEvent* ev)
{
  FKey key_id = ev->key();
  bool is_last_line{false};

  if ( getPrintPos().getY() == int(getDesktopHeight()) )
    is_last_line = true;

  print() << "Key " << getKeyName(key_id).c_str()
          << " (id " << key_id << ")\n";

  if ( is_last_line )
    scrollAreaForward (getVirtualDesktop());

  setAreaCursor ( finalcut::FPoint(1, getPrintPos().getY())
                , true, getVirtualDesktop() );
}

//----------------------------------------------------------------------
void Keyboard::onAccel (finalcut::FAccelEvent* ev)
{
  quit();
  ev->accept();
}

//----------------------------------------------------------------------
void Keyboard::draw()
{
  print() << finalcut::FPoint(1, 1)
          << "---------------\n"
          << "Press Q to quit\n"
          << "---------------\n";
  setAreaCursor (finalcut::FPoint(1, 4), true, getVirtualDesktop());
}

//----------------------------------------------------------------------
//                               main part
//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
  // Create the application object
  finalcut::FApplication app(argc, argv);
  app.setForegroundColor(finalcut::fc::Default);
  app.setBackgroundColor(finalcut::fc::Default);

  // Create a keyboard object
  Keyboard key(&app);
  key.addAccelerator('q');

  // Set the keyboard object as main widget
  app.setMainWidget(&key);

  // Show and start the application
  key.show();
  return app.exec();
}
