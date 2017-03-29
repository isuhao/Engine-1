/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widget.cpp
!*/

#include "GUI/Widget.h"

Widget::Widget(const Vec2& pos, const Vec2& size, Camera* cam):
    _visible(true), _bg_visible(true)
{
    Object::SetSize(size);
    _back.SetFrameSize(size);
    SetPos(pos);
    _camera = cam;
}

Widget::~Widget() {
    if (_back.GetTexture() != nullptr) {
        SDL_DestroyTexture(_back.GetTexture());
    }
}

void Widget::Show(bool show){
    _visible = show;
}

void Widget::ShowBack(bool show_bg){
    _bg_visible = show_bg;
}

void Widget::SetBackGround(const std::string& tileset,const Vec2& skin, int tile_size) {
    if(_back.GetTexture() != nullptr){
        SDL_DestroyTexture(_back.GetTexture());
    }

    //TODO FIX THIS
    if(tileset.empty()){
        return;
    }

    SDL_Texture *texture_skin = Resources::GetTexture(tileset);

    if(!texture_skin){
        return;
    }

    SDL_Rect rect = {0, 0, static_cast<int>(GetSize().x), static_cast<int>(GetSize().y)};

    SDL_Texture *texture_back = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                                  SDL_TEXTUREACCESS_TARGET, rect.w,
                                                  rect.h);
    SDL_SetTextureBlendMode(texture_back, SDL_BLENDMODE_BLEND);

    //SDL_Texture *texture_skin = Resources::GetTexture(tileset);
    Surface::GetSkinnedRect(texture_skin, texture_back, &skin, &rect, tile_size);

    _back.SetTexture(texture_back);
}

void Widget::SetCamera(Camera *cam){
    _camera = cam;
}

void Widget::Connect(Object *obj){
    Object::Connect(obj);

    Widget* wgt = dynamic_cast<Widget*>(obj);
    if(wgt){
        wgt->_camera = this->_camera;
    }
}

const bool& Widget::IsVisible() const{
    return _visible;
}

const bool& Widget::BackIsVisible() const{
    return _bg_visible;
}
