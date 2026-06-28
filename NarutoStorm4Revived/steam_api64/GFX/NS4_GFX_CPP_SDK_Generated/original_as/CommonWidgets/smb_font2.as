package script.xcmn_font
{
   import Language.LanguageKeyCode;
   import flash.display.BlendMode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.geom.Point;
   import flash.geom.Rectangle;
   import flash.text.TextField;
   import flash.text.TextFieldAutoSize;
   import flash.text.TextFormat;
   import flash.text.TextFormatAlign;
   import script.xcmn_btn_plat.all_btn_plat;
   
   public class smb_font2 extends FontParam
   {
      
      public static const CCD_COLOR_RED:uint = 12068613;
      
      public static const CCD_COLOR_L_RED:uint = 12068613;
      
      public static const CCD_COLOR_GREEN:uint = 10823948;
      
      public static const CCD_COLOR_BLUE:uint = 8769791;
      
      public static const CCD_COLOR_WHITE:uint = 16777215;
      
      public static const CCD_COLOR_BLACK:uint = 0;
      
      public static const CCD_FONT_SIZE_SMALL:uint = 28;
      
      public static const CCD_FONT_SIZE_MIDDLE:uint = 33;
      
      public static const CCD_FONT_SIZE_LARGE:uint = 37;
      
      public static const CCD_PIVOT_LT:uint = CCD_PIVOT_H_LEFT | CCD_PIVOT_V_TOP;
      
      public static const CCD_PIVOT_LC:uint = CCD_PIVOT_H_LEFT | CCD_PIVOT_V_CENTER;
      
      public static const CCD_PIVOT_LB:uint = CCD_PIVOT_H_LEFT | CCD_PIVOT_V_BOTTOM;
      
      public static const CCD_PIVOT_CT:uint = CCD_PIVOT_H_CENTER | CCD_PIVOT_V_TOP;
      
      public static const CCD_PIVOT_CC:uint = CCD_PIVOT_H_CENTER | CCD_PIVOT_V_CENTER;
      
      public static const CCD_PIVOT_CB:uint = CCD_PIVOT_H_CENTER | CCD_PIVOT_V_BOTTOM;
      
      public static const CCD_PIVOT_RT:uint = CCD_PIVOT_H_RIGHT | CCD_PIVOT_V_TOP;
      
      public static const CCD_PIVOT_RC:uint = CCD_PIVOT_H_RIGHT | CCD_PIVOT_V_CENTER;
      
      public static const CCD_PIVOT_RB:uint = CCD_PIVOT_H_RIGHT | CCD_PIVOT_V_BOTTOM;
      
      public static const CCD_ALIGN_LEFT:String = TextFormatAlign.LEFT;
      
      public static const CCD_ALIGN_CENTER:String = TextFormatAlign.CENTER;
      
      public static const CCD_ALIGN_RIGHT:String = TextFormatAlign.RIGHT;
      
      private static const CCD_LEADING_RUBY_ON:int = 6;
      
      private static const CCD_LEADING_RUBY_OFF:int = -4;
      
      private var m_langParam:LanguageKeyCode = new LanguageKeyCode();
      
      private var m_font:TextField = null;
      
      private var m_rubyFont:TextField = null;
      
      private var m_rubyInfoArray:Array = new Array();
      
      private var m_rubyTextArray:Array = new Array();
      
      private var m_textAlign:String = "center";
      
      private var m_textSize:uint = 0;
      
      private var m_textLeading:Number = -4;
      
      private var m_iconScale:Point = new Point();
      
      private var m_iconKeyCode:Array = new Array();
      
      private var m_iconArr:Array = new Array();
      
      private var m_iconMskArr:Array = new Array();
      
      private var m_btnIconMargin_Y:Number = 0;
      
      public function smb_font2()
      {
         super();
         var _loc1_:* = this.m_langParam.GetGameSetLang();
         if(_loc1_ == this.m_langParam.GetJapaneseKeyCode())
         {
            this.m_textLeading = CCD_LEADING_RUBY_ON;
         }
         else if(_loc1_ == this.m_langParam.GetLangChinese_tKeyCode() || _loc1_ == this.m_langParam.GetLangChinese_sKeyCode() || _loc1_ == this.m_langParam.GetLangKoreanKeyCode())
         {
            this.m_textLeading = CCD_LEADING_RUBY_ON;
            this.m_btnIconMargin_Y = CCD_BTN_ICON_REPLACE_Y_MARGIN_UP;
         }
         else
         {
            this.m_btnIconMargin_Y = CCD_BTN_ICON_REPLACE_Y_MARGIN_DOWN;
         }
         this.m_textSize = CCD_FONT_SIZE_MIDDLE;
         this.m_font = TextField(getChildByName("txt"));
         this.m_font.wordWrap = false;
         this.m_font.textColor = CCD_COLOR_WHITE;
         this.m_font.autoSize = TextFieldAutoSize.LEFT;
         var _loc2_:TextFormat = new TextFormat();
         _loc2_.leading = CCD_LEADING_RUBY_OFF;
         _loc2_.size = this.m_textSize;
         this.m_font.setTextFormat(_loc2_);
         this.m_rubyFont = TextField(getChildByName("rubi"));
         this.m_rubyFont.wordWrap = false;
         this.m_rubyFont.textColor = this.m_font.textColor;
         this.m_rubyFont.autoSize = TextFieldAutoSize.LEFT;
         this.m_rubyFont.x = this.m_font.x;
         this.m_rubyFont.y = this.m_font.y - this.m_rubyFont.height / 1.5 + CCD_RUBI_GAP;
         removeChild(this.m_rubyFont);
         this.SetTextSize(CCD_FONT_SIZE_MIDDLE);
         if(_loc1_ == this.m_langParam.GetArabicKeyCode())
         {
            InitializeArabicParam();
         }
         var _loc3_:MovieClip = this["mc_msk"];
         removeChild(_loc3_);
         addEventListener(Event.REMOVED_FROM_STAGE,this.Removed);
      }
      
      public function Removed(param1:Event) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.m_rubyTextArray.length)
         {
            removeChild(this.m_rubyTextArray[_loc2_]);
            _loc2_++;
         }
         this.m_rubyTextArray.length = 0;
         removeEventListener(Event.REMOVED_FROM_STAGE,this.Removed);
      }
      
      public function SetText(param1:String) : *
      {
         var _loc3_:TextFormat = null;
         this.m_font.text = param1;
         var _loc2_:int = -1;
         while(1)
         {
            _loc2_ = this.m_font.text.indexOf("%%",_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            this.m_font.replaceText(_loc2_,_loc2_ + 2,"%");
         }
         if(this.m_font.defaultTextFormat.size != this.m_textSize)
         {
            _loc3_ = new TextFormat();
            _loc3_.size = this.m_textSize;
            _loc3_.align = this.m_textAlign;
            _loc3_.leading = this.m_textLeading;
            this.m_font.setTextFormat(_loc3_);
         }
         this.CalcTagText();
         if(this.m_langParam.GetGameSetLang() == this.m_langParam.GetArabicKeyCode())
         {
            ConvertArabic(this.m_font);
         }
         this.CreateIconMask();
         trace(this.m_font.text);
      }
      
      public function SetTextColor(param1:uint) : *
      {
         this.m_font.textColor = param1;
         this.m_rubyFont.textColor = param1;
      }
      
      public function SetTextLineColor(param1:uint, param2:uint) : *
      {
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         var _loc5_:TextFormat = null;
         if(param1 < this.m_font.numLines)
         {
            _loc3_ = this.m_font.getLineOffset(param1);
            _loc4_ = _loc3_ + this.m_font.getLineLength(param1);
            _loc5_ = new TextFormat();
            _loc5_.color = param2;
            this.m_font.setTextFormat(_loc5_,_loc3_,_loc4_);
         }
      }
      
      public function SetTextAlign(param1:*) : *
      {
         var _loc2_:TextFormat = null;
         if(param1 != this.m_textAlign)
         {
            this.m_textAlign = param1;
            _loc2_ = new TextFormat();
            _loc2_.align = this.m_textAlign;
            this.m_font.setTextFormat(_loc2_);
         }
      }
      
      public function SetTextSize(param1:uint) : *
      {
         this.m_textSize = param1;
         var _loc2_:TextFormat = new TextFormat();
         _loc2_.size = this.m_textSize;
         this.m_font.setTextFormat(_loc2_);
      }
      
      public function SetTextWordWrap(param1:Boolean, param2:Number) : *
      {
         this.m_font.wordWrap = param1;
         if(param1 == true)
         {
            this.m_font.width = param2;
         }
      }
      
      public function SetTextFieldWidth(param1:Number) : *
      {
         this.m_font.width = param1;
      }
      
      public function SetTextRubyEnable(param1:Boolean) : *
      {
         var _loc2_:TextFormat = new TextFormat();
         this.ReleaseRubyText();
         if(param1 == true)
         {
            _loc2_.leading = CCD_LEADING_RUBY_ON;
            this.m_font.setTextFormat(_loc2_);
         }
         else
         {
            _loc2_.leading = CCD_LEADING_RUBY_OFF;
            this.m_font.setTextFormat(_loc2_);
         }
      }
      
      public function ReplaceTextList(param1:Array) : *
      {
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:int = 0;
         var _loc7_:Number = NaN;
         var _loc2_:int = -1;
         var _loc3_:uint = 0;
         while(1)
         {
            _loc2_ = -1;
            _loc2_ = this.m_font.text.indexOf(CCD_TAG_TEXT_STRING,_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            _loc4_ = this.m_font.text.indexOf("/>",_loc2_);
            if(_loc4_ == -1)
            {
               break;
            }
            _loc5_ = -1;
            _loc6_ = 0;
            _loc6_ = _loc2_;
            while(_loc6_ < _loc4_)
            {
               _loc7_ = this.m_font.text.charCodeAt(_loc6_);
               if(_loc7_ >= 48 && _loc7_ <= 57)
               {
                  _loc5_ = _loc7_ - 48;
                  break;
               }
               _loc6_++;
            }
            if(_loc5_ != -1)
            {
               if(_loc5_ > param1.length)
               {
                  break;
               }
               this.m_font.replaceText(_loc2_,_loc4_ + 2,param1[_loc5_ - 1]);
            }
            else
            {
               this.m_font.replaceText(_loc2_,_loc4_ + 2,param1[_loc3_]);
               _loc3_++;
               if(_loc3_ >= param1.length)
               {
                  break;
               }
            }
            _loc2_ = _loc4_;
         }
      }
      
      public function GetTextFieldWidth() : Number
      {
         return this.m_font.width;
      }
      
      public function GetTextFieldHeight() : Number
      {
         return this.m_font.height;
      }
      
      public function GetRubyTextHeight() : Number
      {
         var _loc1_:Number = 0;
         if(this.m_rubyTextArray.length > 0)
         {
            _loc1_ = Number(this.m_rubyTextArray[0].height);
         }
         return _loc1_;
      }
      
      public function GetSymbolHeight() : Number
      {
         return height;
      }
      
      public function GetTextNumlines() : int
      {
         return this.m_font.numLines;
      }
      
      public function GetTextLineY(param1:int) : Number
      {
         var _loc3_:int = 0;
         var _loc2_:Number = -1;
         if(param1 >= 0 && param1 < this.m_font.numLines)
         {
            _loc3_ = this.m_font.getLineOffset(param1);
            if(_loc3_ >= 0)
            {
               _loc2_ = y;
               _loc2_ += this.m_font.getCharBoundaries(_loc3_).y - this.m_font.y;
            }
         }
         return _loc2_;
      }
      
      public function GetTextSize() : uint
      {
         return uint(this.m_font.defaultTextFormat.size);
      }
      
      public function GetTextColor() : uint
      {
         return this.m_font.textColor;
      }
      
      public function SetPlayerSide(param1:int) : *
      {
         m_playerSide = param1;
         SetPlayerActIconTag();
      }
      
      public function IsWordWrap() : Boolean
      {
         return this.m_font.wordWrap;
      }
      
      private function ReleaseRubyText() : *
      {
         var _loc1_:String = null;
         for(_loc1_ in this.m_rubyTextArray)
         {
            removeChild(this.m_rubyTextArray[_loc1_]);
         }
         this.m_rubyTextArray.length = 0;
      }
      
      private function CalcTagText() : *
      {
         if(this.m_langParam.GetGameSetLang() == this.m_langParam.GetJapaneseKeyCode())
         {
            CreateRubyInfo(this.m_font,this.m_rubyInfoArray);
         }
         this.CreateIconKeyCode();
         this.ChangeIconKeyCode();
         if(this.m_langParam.GetGameSetLang() != this.m_langParam.GetArabicKeyCode())
         {
            this.ColoringText();
         }
         else
         {
            this.ColoringArabicText();
         }
         if(this.m_langParam.GetGameSetLang() == this.m_langParam.GetJapaneseKeyCode())
         {
            InsertRuby(this,this.m_font,this.m_rubyFont.defaultTextFormat,this.m_rubyInfoArray,this.m_rubyTextArray);
         }
      }
      
      private function CreateIconMask() : *
      {
         var _loc2_:Array = null;
         var _loc3_:int = 0;
         var _loc4_:Object = null;
         var _loc5_:int = 0;
         var _loc6_:int = 0;
         var _loc7_:Rectangle = null;
         var _loc8_:Rectangle = null;
         var _loc9_:String = null;
         var _loc10_:smb_msk = null;
         var _loc1_:int = 0;
         while(_loc1_ < this.m_iconMskArr.length)
         {
            removeChild(this.m_iconMskArr[_loc1_]);
            _loc1_++;
         }
         this.m_iconMskArr.length = 0;
         if(this.m_iconArr.length != 0)
         {
            if(this.m_langParam.GetGameSetLang() != this.m_langParam.GetArabicKeyCode())
            {
               _loc2_ = new Array();
               _loc2_.push(-1);
               _loc2_.push(-1);
               _loc3_ = 0;
               while(1)
               {
                  _loc4_ = GetUseKeyCodeIndex(this.m_font.text,_loc2_,this.m_iconKeyCode);
                  _loc5_ = int(_loc4_[CCD_USE_INDEX]);
                  _loc6_ = int(_loc4_[CCD_USE_KEY_CODE_TYPE]);
                  if(!(_loc5_ != -1 && this.m_iconArr[_loc3_] != undefined))
                  {
                     break;
                  }
                  _loc7_ = new Rectangle();
                  _loc8_ = new Rectangle();
                  _loc9_ = this.m_iconKeyCode[_loc6_];
                  _loc10_ = new smb_msk();
                  _loc10_.blendMode = BlendMode.ERASE;
                  _loc7_ = this.m_font.getCharBoundaries(_loc5_);
                  _loc8_ = this.m_font.getCharBoundaries(_loc5_ + _loc9_.length - 1);
                  _loc10_.width = Math.abs(_loc8_.right - _loc7_.left);
                  _loc10_.x = _loc7_.left + this.m_font.x + _loc10_.width / 2;
                  _loc10_.height = Number(this.m_font.defaultTextFormat.size);
                  _loc10_.y = _loc7_.y + this.m_font.y + _loc10_.height / 2 + CCD_ICON_MASK_Y_MARGIN;
                  _loc10_.height += CCD_ICON_MASK_HEIGHT_MARGIN;
                  addChild(_loc10_);
                  this.m_iconMskArr.push(_loc10_);
                  _loc2_[_loc6_] = _loc5_ + this.m_iconKeyCode[_loc6_].length;
                  _loc3_++;
               }
            }
            else
            {
               CreateMaskArabic(this,this.m_font,this.m_iconKeyCode,this.m_iconArr,this.m_iconMskArr);
            }
         }
      }
      
      private function CalcMaskPos() : *
      {
         var _loc1_:Array = null;
         var _loc2_:int = 0;
         var _loc3_:Object = null;
         var _loc4_:int = 0;
         var _loc5_:Rectangle = null;
         var _loc6_:Rectangle = null;
         var _loc7_:int = 0;
         var _loc8_:String = null;
         if(this.m_langParam.GetGameSetLang() != this.m_langParam.GetArabicKeyCode())
         {
            _loc1_ = new Array();
            _loc1_.push(-1);
            _loc1_.push(-1);
            _loc2_ = 0;
            while(1)
            {
               _loc3_ = GetUseKeyCodeIndex(this.m_font.text,_loc1_,this.m_iconKeyCode);
               _loc4_ = int(_loc3_[CCD_USE_INDEX]);
               if(!(_loc4_ != -1 && this.m_iconArr[_loc2_] != undefined))
               {
                  break;
               }
               _loc5_ = new Rectangle();
               _loc6_ = new Rectangle();
               _loc7_ = int(_loc3_[CCD_USE_KEY_CODE_TYPE]);
               _loc8_ = this.m_iconKeyCode[_loc7_];
               _loc5_ = this.m_font.getCharBoundaries(_loc4_);
               _loc6_ = this.m_font.getCharBoundaries(_loc4_ + _loc8_.length - 1);
               this.m_iconMskArr[_loc2_].x = _loc5_.left + this.m_font.x + this.m_iconMskArr[_loc2_].width / 2 + 2;
               this.m_iconMskArr[_loc2_].y = _loc5_.y + this.m_font.y + this.m_iconMskArr[_loc2_].height / 2 + CCD_ICON_MASK_Y_MARGIN;
               _loc1_[_loc7_] = _loc4_ + this.m_iconKeyCode[_loc7_].length;
               _loc2_++;
            }
         }
         else
         {
            CalcMaskPosArabic(this.m_font,this.m_iconKeyCode,this.m_iconMskArr);
         }
      }
      
      private function ColoringText() : *
      {
         var _loc2_:uint = 0;
         var _loc3_:uint = 0;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:TextFormat = null;
         var _loc7_:int = 0;
         var _loc1_:int = -1;
         while(1)
         {
            _loc1_ = this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_S,_loc1_);
            if(_loc1_ == -1)
            {
               break;
            }
            _loc2_ = CCD_COLOR_WHITE;
            _loc3_ = 0;
            _loc4_ = _loc1_ + CCD_TAG_TEXT_COLORING_S.length;
            switch(this.m_font.text.charAt(_loc4_))
            {
               case CCD_TAG_TEXT_COLORING_RED.charAt():
                  _loc2_ = CCD_COLOR_RED;
                  _loc3_ = uint(CCD_TAG_TEXT_COLORING_RED.length);
                  break;
               case CCD_TAG_TEXT_COLORING_BLUE.charAt():
                  _loc2_ = CCD_COLOR_BLUE;
                  _loc3_ = uint(CCD_TAG_TEXT_COLORING_BLUE.length);
                  break;
               case CCD_TAG_TEXT_COLORING_RED_L.charAt():
                  if(this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_RED_L,_loc4_) == _loc4_)
                  {
                     _loc2_ = CCD_COLOR_L_RED;
                     _loc3_ = uint(CCD_TAG_TEXT_COLORING_RED_L.length);
                  }
            }
            _loc5_ = this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_E,_loc1_ + 1);
            if(_loc5_ == -1)
            {
               trace("CalcTagText::Coloring Error!!");
               break;
            }
            _loc6_ = new TextFormat();
            _loc6_.color = _loc2_;
            _loc7_ = _loc1_ + CCD_TAG_TEXT_COLORING_S.length;
            this.m_font.setTextFormat(_loc6_,_loc4_ + _loc3_,_loc5_);
            this.m_font.replaceText(_loc5_,_loc5_ + CCD_TAG_TEXT_COLORING_E.length,"");
            this.m_font.replaceText(_loc1_,_loc1_ + CCD_TAG_TEXT_COLORING_S.length + _loc3_,"");
         }
      }
      
      private function ColoringArabicText() : *
      {
         var _loc2_:uint = 0;
         var _loc3_:uint = 0;
         var _loc4_:String = null;
         var _loc5_:* = 0;
         var _loc6_:Number = NaN;
         var _loc7_:int = 0;
         var _loc8_:Number = NaN;
         var _loc9_:TextFormat = null;
         var _loc10_:int = 0;
         var _loc1_:int = -1;
         while(1)
         {
            _loc1_ = this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_S,_loc1_);
            if(_loc1_ == -1)
            {
               break;
            }
            _loc2_ = CCD_COLOR_WHITE;
            _loc3_ = uint(CCD_TAG_TEXT_COLORING_S.length);
            _loc4_ = this.m_font.text.charAt(_loc1_ + _loc3_);
            switch(_loc4_)
            {
               case CCD_TAG_TEXT_COLORING_RED.charAt():
                  _loc2_ = CCD_COLOR_RED;
                  _loc3_ += CCD_TAG_TEXT_COLORING_RED.length;
                  _loc4_ = CCD_TAG_TEXT_COLORING_RED;
                  break;
               case CCD_TAG_TEXT_COLORING_BLUE.charAt():
                  _loc2_ = CCD_COLOR_BLUE;
                  _loc3_ += CCD_TAG_TEXT_COLORING_BLUE.length;
                  _loc4_ = CCD_TAG_TEXT_COLORING_BLUE;
                  break;
               case CCD_TAG_TEXT_COLORING_RED_L.charAt():
                  if(this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_RED_L,_loc1_ + _loc3_) == _loc1_ + _loc3_)
                  {
                     _loc2_ = CCD_COLOR_L_RED;
                     _loc3_ += CCD_TAG_TEXT_COLORING_RED_L.length;
                     _loc4_ = CCD_TAG_TEXT_COLORING_RED_L;
                  }
            }
            _loc5_ = _loc1_;
            while(1)
            {
               _loc5_--;
               _loc6_ = this.m_font.text.charCodeAt(_loc5_);
               if(_loc6_ >= 1536 && _loc6_ <= 1791)
               {
                  _loc5_++;
                  break;
               }
               if(_loc5_ == -1)
               {
                  _loc5_ = 0;
                  break;
               }
            }
            if(_loc5_ != _loc1_ - 1)
            {
               _loc7_ = this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_E,_loc5_ - 1);
               if(_loc7_ < _loc1_ && _loc7_ != -1)
               {
                  this.m_font.replaceText(_loc1_,_loc1_ + _loc3_,CCD_TAG_TEXT_COLORING_E);
                  this.m_font.replaceText(_loc7_,_loc7_ + CCD_TAG_TEXT_COLORING_E.length,CCD_TAG_TEXT_COLORING_S + _loc4_);
                  _loc1_ = _loc7_;
               }
               else
               {
                  _loc8_ = this.m_font.text.charCodeAt(_loc1_ + CCD_TAG_TEXT_COLORING_S.length);
                  if(_loc8_ >= 1536 && _loc8_ <= 1791)
                  {
                     this.m_font.replaceText(_loc1_,_loc1_ + CCD_TAG_TEXT_COLORING_S.length + _loc3_,"");
                     this.m_font.replaceText(_loc5_,_loc5_ + 1,this.m_font.text.charAt(_loc5_) + CCD_TAG_TEXT_COLORING_S + _loc4_);
                     _loc1_ = _loc5_;
                  }
               }
            }
            _loc7_ = this.m_font.text.indexOf(CCD_TAG_TEXT_COLORING_E,_loc1_ + 1);
            if(_loc7_ == -1)
            {
               trace("CalcTagText::Coloring Error!!");
               break;
            }
            _loc9_ = new TextFormat();
            _loc9_.color = _loc2_;
            _loc10_ = _loc1_ + CCD_TAG_TEXT_COLORING_S.length;
            this.m_font.setTextFormat(_loc9_,_loc1_ + CCD_TAG_TEXT_COLORING_S.length,_loc7_);
            this.m_font.replaceText(_loc7_,_loc7_ + CCD_TAG_TEXT_COLORING_E.length,"");
            this.m_font.replaceText(_loc1_,_loc1_ + _loc3_,"");
         }
      }
      
      private function ChangeIconKeyCode() : *
      {
         var _loc1_:* = undefined;
         var _loc3_:String = null;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         this.m_iconArr.length = 0;
         var _loc2_:int = -1;
         while(1)
         {
            _loc2_ = this.m_font.text.indexOf(CCD_TAG_TEXT_ICON,_loc2_);
            if(_loc2_ == -1)
            {
               break;
            }
            if(this.ChangePlusIconKeyCode(_loc2_) == false)
            {
               _loc3_ = new String();
               _loc4_ = this.m_font.text.indexOf(">",_loc2_ + 1);
               if(_loc4_ == -1)
               {
                  break;
               }
               _loc3_ = this.GetIconLabel(_loc2_,_loc4_ + 1);
               if(_loc3_.length != 0)
               {
                  _loc5_ = GetKeyCodeType(_loc3_);
                  if(_loc5_ != -1)
                  {
                     this.m_font.replaceText(_loc2_,_loc4_ + 1,this.m_iconKeyCode[_loc5_]);
                     this.m_iconArr.push(_loc3_);
                  }
               }
               else
               {
                  _loc2_ = _loc4_ + 1;
               }
            }
         }
      }
      
      private function ChangePlusIconKeyCode(param1:int) : Boolean
      {
         var _loc5_:int = 0;
         var _loc6_:Boolean = false;
         var _loc7_:int = 0;
         var _loc8_:int = 0;
         var _loc2_:Boolean = false;
         var _loc3_:int = this.m_font.text.indexOf(CCD_TAG_TEXT_PLUS_1);
         var _loc4_:int = this.m_font.text.indexOf(CCD_TAG_TEXT_PLUS_2);
         if(_loc3_ == -1)
         {
            _loc3_ = _loc4_;
         }
         else if(_loc4_ < _loc3_)
         {
            if(_loc4_ != -1)
            {
               _loc3_ = _loc4_;
            }
         }
         if(_loc3_ != -1 && _loc3_ < param1)
         {
            _loc5_ = _loc3_ + 1;
            if(_loc3_ + 2 < this.m_font.text.length)
            {
               if(this.m_font.text.charAt(_loc3_ + 1) == " ")
               {
                  _loc6_ = true;
                  _loc7_ = this.m_font.text.indexOf(this.m_iconKeyCode[CCD_KEY_CODE],_loc3_ + 1);
                  _loc8_ = this.m_font.text.indexOf(this.m_iconKeyCode[CCD_KEY_CODE_WIDE],_loc3_ + 1);
                  if(_loc7_ != 1 && _loc7_ == _loc3_ + 1)
                  {
                     _loc6_ = false;
                  }
                  else if(_loc8_ != 1 && _loc8_ == _loc3_ + 1)
                  {
                     _loc6_ = false;
                  }
                  if(_loc6_ == true)
                  {
                     _loc5_ = _loc3_ + 2;
                  }
               }
            }
            if(_loc3_ - 1 >= 0)
            {
               if(this.m_font.text.charAt(_loc3_ - 1) == " ")
               {
                  _loc6_ = true;
                  _loc7_ = this.m_font.text.lastIndexOf(this.m_iconKeyCode[CCD_KEY_CODE],_loc3_ - 1);
                  _loc8_ = this.m_font.text.lastIndexOf(this.m_iconKeyCode[CCD_KEY_CODE_WIDE],_loc3_ - 1);
                  if(_loc7_ != 1 && _loc7_ + this.m_iconKeyCode[CCD_KEY_CODE].length == _loc3_)
                  {
                     _loc6_ = false;
                  }
                  else if(_loc8_ != 1 && _loc8_ + this.m_iconKeyCode[CCD_KEY_CODE_WIDE].length == _loc3_)
                  {
                     _loc6_ = false;
                  }
                  if(_loc6_ == true)
                  {
                     _loc3_--;
                  }
               }
            }
            this.m_font.replaceText(_loc3_,_loc5_,this.m_iconKeyCode[CCD_KEY_CODE]);
            this.m_iconArr.push("icon_plus");
            _loc2_ = true;
         }
         return _loc2_;
      }
      
      private function GetIconLabel(param1:int, param2:int) : String
      {
         var _loc3_:String = this.m_font.text.substring(param1,param2);
         var _loc4_:String = "";
         if(m_btnIconMap[_loc3_] != undefined)
         {
            _loc4_ = m_btnIconMap[_loc3_];
         }
         return _loc4_;
      }
      
      private function CreateIconKeyCode() : *
      {
         var _loc4_:Number = NaN;
         var _loc5_:TextField = null;
         var _loc6_:TextFormat = null;
         var _loc7_:String = null;
         var _loc1_:Number = this.m_textSize;
         this.m_iconScale.x = 0.45 * (Number(_loc1_) / CCD_FONT_SIZE_MIDDLE);
         this.m_iconScale.y = 0.45 * (Number(_loc1_) / CCD_FONT_SIZE_MIDDLE);
         var _loc2_:String = "";
         var _loc3_:int = 0;
         while(_loc3_ < 2)
         {
            _loc4_ = CCD_ICON_KEY_CODE_WIDTH * this.m_iconScale.x;
            _loc2_ = "\"";
            if(_loc3_ == 1)
            {
               _loc4_ = CCD_ICON_KEY_CODE_WIDTH_WIDE * this.m_iconScale.x;
               _loc2_ = "\'";
            }
            _loc5_ = new TextField();
            _loc6_ = new TextFormat();
            _loc6_.size = _loc1_;
            _loc6_.font = this.m_font.defaultTextFormat.font;
            _loc5_.defaultTextFormat = _loc6_;
            _loc5_.wordWrap = false;
            _loc5_.multiline = false;
            _loc5_.autoSize = TextFieldAutoSize.LEFT;
            _loc5_.text = " ";
            _loc5_.appendText(_loc2_);
            _loc7_ = _loc5_.text;
            while(1)
            {
               _loc5_.appendText(" ");
               if(_loc5_.width >= _loc4_)
               {
                  _loc7_ = _loc5_.text;
                  break;
               }
               _loc5_.replaceText(_loc5_.length - 1,_loc5_.length,_loc2_);
            }
            this.m_iconKeyCode.push(_loc7_);
            _loc3_++;
         }
      }
      
      internal function CreateIcon(param1:MovieClip, param2:Array) : *
      {
         var _loc4_:Array = null;
         var _loc5_:int = 0;
         var _loc6_:Object = null;
         var _loc7_:int = 0;
         var _loc8_:Number = NaN;
         var _loc9_:MovieClip = null;
         var _loc10_:int = 0;
         var _loc11_:String = null;
         var _loc3_:int = 0;
         while(_loc3_ < param2.length)
         {
            param1.removeChild(param2[_loc3_]);
            _loc3_++;
         }
         param2.length = 0;
         if(this.m_iconArr.length != 0)
         {
            _loc4_ = new Array();
            _loc4_.push(-1);
            _loc4_.push(-1);
            _loc5_ = 0;
            while(1)
            {
               _loc6_ = GetUseKeyCodeIndex(this.m_font.text,_loc4_,this.m_iconKeyCode);
               _loc7_ = int(_loc6_[CCD_USE_INDEX]);
               _loc8_ = CCD_ICON_REPLACE_Y_MARGIN;
               if(!(_loc7_ != -1 && this.m_iconArr[_loc5_] != undefined))
               {
                  break;
               }
               _loc9_ = null;
               if(this.m_iconArr[_loc5_].indexOf("txt") != -1)
               {
                  _loc9_ = new anm_icon();
                  _loc9_.name = "txtIcon" + _loc5_;
                  _loc9_.gotoAndStop(this.m_iconArr[_loc5_]);
                  _loc9_.CreateIcon(uint(this.m_font.getTextFormat(_loc7_,_loc7_ + 1).color));
               }
               else
               {
                  _loc11_ = "icon";
                  if(this.m_iconArr[_loc5_].indexOf("btn") != -1 || this.m_iconArr[_loc5_].indexOf("plus") != -1)
                  {
                     _loc11_ = "dispIcon";
                     _loc8_ += this.m_btnIconMargin_Y;
                  }
                  _loc9_ = new all_btn_plat();
                  _loc9_.name = _loc11_ + _loc5_;
                  _loc9_.gotoAndStop(this.m_iconArr[_loc5_]);
               }
               _loc9_.scaleX = this.m_iconScale.x;
               _loc9_.scaleY = this.m_iconScale.y;
               _loc9_.x = this.m_iconMskArr[_loc5_].x;
               _loc9_.y = this.m_iconMskArr[_loc5_].y;
               _loc9_.x += x + CCD_ICON_REPLACE_X_MARGIN * _loc9_.scaleX;
               _loc9_.y += y + _loc8_ * _loc9_.scaleY;
               param1.addChild(_loc9_);
               param2.push(_loc9_);
               _loc10_ = int(_loc6_[CCD_USE_KEY_CODE_TYPE]);
               _loc4_[_loc10_] = _loc7_ + this.m_iconKeyCode[_loc10_].length;
               _loc5_++;
            }
         }
      }
      
      internal function CalcIconPos(param1:MovieClip, param2:Array) : *
      {
         var _loc4_:Number = NaN;
         this.CalcMaskPos();
         var _loc3_:uint = 0;
         _loc3_ = 0;
         while(_loc3_ < param2.length)
         {
            if(this.m_iconMskArr[_loc3_] != undefined)
            {
               param2[_loc3_].x = this.m_iconMskArr[_loc3_].x + CCD_ICON_REPLACE_X_MARGIN * param2[_loc3_].scaleX;
               _loc4_ = CCD_ICON_REPLACE_Y_MARGIN;
               if(param2[_loc3_].name.indexOf("dispIcon") != -1)
               {
                  _loc4_ += this.m_btnIconMargin_Y;
               }
               param2[_loc3_].y = this.m_iconMskArr[_loc3_].y + _loc4_ * param2[_loc3_].scaleY;
               param2[_loc3_].x += x;
               param2[_loc3_].y += y;
            }
            _loc3_++;
         }
      }
      
      internal function ResetRuby() : *
      {
         if(this.m_langParam.GetGameSetLang() == this.m_langParam.GetJapaneseKeyCode())
         {
            InsertRuby(this,this.m_font,this.m_rubyFont.defaultTextFormat,this.m_rubyInfoArray,this.m_rubyTextArray);
         }
      }
      
      public function SetTextBorder(param1:Boolean) : *
      {
         this.m_font.border = param1;
      }
      
      public function SetTextBorderColor(param1:uint) : *
      {
         this.m_font.borderColor = param1;
      }
      
      public function GetText() : String
      {
         return this.m_font.text;
      }
   }
}

