package script.xcmn_unset
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   public class nut_xcmn_win00 extends MovieClip
   {
      
      private static const CCD_WINDOW_BLANK_Y:* = 18;
      
      private static const CCD_WINDOW_INS_BLANK_Y:* = 32;
      
      public static const CCD_WINDOW_MARGIN_X:* = 100;
      
      public static const CCD_WINDOW_MARGIN_Y:* = CCD_WINDOW_BLANK_Y + CCD_WINDOW_INS_BLANK_Y;
      
      private static const CCD_CURSOR_MARGIN_X:* = 28;
      
      private static const CCD_TITLE_MARGIN_Y:* = 28;
      
      public const CCD_CLOSED_FRAME:int = 14;
      
      public var ChangeAnimLoop:Function;
      
      public var ChangeAnimClosed:Function;
      
      public var GetSelValue:Function;
      
      public var GetDispNo:Function;
      
      public var GetDispSelValue:Function;
      
      private var m_win:MovieClip;
      
      private var m_cursor:MovieClip;
      
      private var m_dispMenuArr:Array;
      
      private var m_menuNum:uint = 1;
      
      private var m_title:smb_font = null;
      
      private var m_line:MovieClip;
      
      private var m_menuArr:Array = new Array();
      
      private var m_textColor:uint;
      
      private var m_textSize:uint;
      
      private var m_textLeader:Number;
      
      private var m_isMsgId:Boolean = false;
      
      private var m_oldLabel:String;
      
      private var m_isFitText:Boolean = true;
      
      private var m_isDispSel:Boolean = false;
      
      private var m_wordWrapWidth:Number = -1;
      
      private var m_line_num:int = -1;
      
      private var m_maxWidth:Number = 0;
      
      public function nut_xcmn_win00()
      {
         super();
         this.m_dispMenuArr = new Array();
         this.m_dispMenuArr.push(smb_font(getChildByName("txt_win00")));
         this.m_cursor = MovieClip(getChildByName("mc_actbar"));
         this.m_textColor = this.m_dispMenuArr[0].GetTextColor();
         this.m_textSize = this.m_dispMenuArr[0].GetTextSize();
         this.m_textLeader = 0;
         this.m_win = MovieClip(getChildByName("mc_win00"));
         this.m_line = MovieClip(getChildByName("mc_line"));
         this.m_line.visible = false;
      }
      
      public function OpenWindow() : *
      {
         gotoAndPlay("in");
         this.m_oldLabel = "in";
         this.VisibleTextCursor(false);
      }
      
      public function CloseWindow() : *
      {
         gotoAndPlay("out");
         this.m_oldLabel = "out";
         this.VisibleTextCursor(false);
      }
      
      public function UpdateSelect() : *
      {
         var _loc2_:* = undefined;
         var _loc3_:* = undefined;
         var _loc1_:String = currentLabel;
         if(_loc1_ == "loop")
         {
            _loc2_ = this.GetDispNo();
            _loc3_ = this.GetSelValue();
            if(this.m_isDispSel == true)
            {
               this.SetCursor(this.GetDispSelValue());
               this.ScrollMsg(_loc2_);
               trace("oldDispNo:nowDispNo = " + _loc2_ + ", " + this.GetDispNo());
               if(_loc2_ != this.GetDispNo())
               {
                  ExternalInterface.call("RequestPlaySE_Select");
               }
            }
            else
            {
               this.SetCursor(this.GetSelValue());
               trace("oldSelVal:nowSelVal = " + _loc3_ + ", " + this.GetSelValue());
               if(_loc3_ != this.GetSelValue())
               {
                  ExternalInterface.call("RequestPlaySE_Select");
               }
            }
            if(this.m_oldLabel != _loc1_)
            {
               this.VisibleTextCursor(true);
            }
         }
         this.m_oldLabel = _loc1_;
      }
      
      public function EntryOnFrameUpdata() : *
      {
         addEventListener(Event.ENTER_FRAME,this.OnFrameUpdateSelect);
      }
      
      public function DeleteOnFrameUpdate() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.OnFrameUpdateSelect);
      }
      
      public function OnFrameUpdateSelect(param1:Event) : *
      {
         var _loc3_:* = undefined;
         var _loc2_:String = currentLabel;
         if(_loc2_ == "loop")
         {
            _loc3_ = this.GetDispNo();
            if(this.m_isDispSel == true)
            {
               this.SetCursor(this.GetDispSelValue());
               this.ScrollMsg(_loc3_);
            }
            else
            {
               this.SetCursor(this.GetSelValue());
            }
         }
         if(currentFrame == this.CCD_CLOSED_FRAME)
         {
            this.ChangeAnimClosed();
            this.DeleteOnFrameUpdate();
         }
         else if(this.m_oldLabel != _loc2_ && _loc2_ == "loop")
         {
            this.ChangeAnimLoop();
            this.VisibleTextCursor(true);
         }
         this.m_oldLabel = _loc2_;
      }
      
      public function SetFixedWidth(param1:Number) : *
      {
         this.m_win.smb_win00.width = param1;
         this.m_isFitText = false;
         this.CalcTextPos();
      }
      
      public function SetFixedHeight(param1:Number) : *
      {
         this.m_win.smb_win00.height = param1;
         this.m_isFitText = false;
         this.CalcTextPos();
      }
      
      public function SetCursor(param1:uint) : *
      {
         if(this.m_dispMenuArr[param1] != null)
         {
            this.m_cursor.x = this.m_dispMenuArr[param1].x + this.m_dispMenuArr[param1].width / 2;
            this.m_cursor.y = this.m_dispMenuArr[param1].y + this.m_dispMenuArr[param1].GetTextFieldHeight() / 2;
         }
      }
      
      public function SetSelectParam(param1:int, param2:Array, param3:Boolean) : *
      {
         this.m_isDispSel = false;
         this.m_menuNum = param2.length;
         this.SetMenu(param2,param3);
         this.SetCursor(param1);
         this.VisibleTextCursor(false);
         this.ResizeWindowSize();
      }
      
      public function SetEnableWordWrap(param1:Number) : *
      {
         if(param1 > CCD_WINDOW_MARGIN_X * 2)
         {
            this.m_wordWrapWidth = param1;
            this.ResizeWindowSize();
         }
      }
      
      public function SetWindowSizeFitText() : *
      {
         this.m_title.SetTextFit(false);
         this.m_title.SetTextWordWrap(false);
         this.m_wordWrapWidth = -1;
         this.ResizeWindowSize();
      }
      
      public function SetDispSelectParam(param1:uint, param2:int, param3:Array, param4:Boolean) : *
      {
         this.m_isDispSel = true;
         this.m_menuNum = param1;
         this.SetMenu(param3,param4);
         this.SetCursor(param2);
         this.VisibleTextCursor(false);
         this.ResizeWindowSize();
      }
      
      public function ResizeWindowSize() : *
      {
         var _loc1_:int = 0;
         var _loc2_:Number = NaN;
         var _loc3_:Number = NaN;
         var _loc4_:* = this.m_dispMenuArr.length;
         _loc3_ = this.m_textLeader * (_loc4_ - 1) + CCD_WINDOW_MARGIN_Y * 2;
         _loc2_ = Number(this.m_dispMenuArr[0].GetTextFieldWidth());
         _loc1_ = 0;
         while(_loc1_ < _loc4_)
         {
            if(this.m_dispMenuArr[_loc1_].GetTextFieldWidth() > _loc2_)
            {
               _loc2_ = Number(this.m_dispMenuArr[_loc1_].GetTextFieldWidth());
            }
            _loc3_ += this.m_dispMenuArr[_loc1_].GetSymbolHeight();
            _loc1_++;
         }
         if(this.m_title != null)
         {
            if(this.m_wordWrapWidth > 0)
            {
               if(this.m_title.GetTextFieldWidth() > this.m_wordWrapWidth)
               {
                  if(this.m_title.GetTextFieldWidth() > _loc2_)
                  {
                     this.m_title.SetTextFieldWidth(this.m_wordWrapWidth);
                     this.m_title.SetTextWordWrap(true);
                  }
               }
               else if(this.m_title.IsWordWrap() == true)
               {
                  if(this.m_title.GetTextNumlines() <= 1)
                  {
                     this.m_title.SetTextWordWrap(false);
                  }
               }
            }
            if(this.m_title.GetTextFieldWidth() > _loc2_)
            {
               _loc2_ = this.m_title.GetTextFieldWidth();
            }
            _loc3_ += this.m_title.GetTextFieldHeight() + CCD_TITLE_MARGIN_Y;
         }
         _loc2_ += CCD_WINDOW_MARGIN_X * 2;
         this.m_win.smb_win00.width = _loc2_;
         this.m_win.smb_win00.height = _loc3_;
         this.m_isFitText = true;
         this.CalcTextPos();
      }
      
      public function SetWindowTitle(param1:String, param2:Boolean) : *
      {
         if(this.m_title != null)
         {
            removeChild(this.m_title);
            this.m_title = null;
         }
         if(param1.length > 0)
         {
            if(param2 == true)
            {
               param1 = String(ExternalInterface.call("MessageConvert",param1));
            }
            this.m_title = new smb_font();
            this.m_title.SetTextAutoSize();
            this.m_title.SetTextColor(this.m_textColor);
            this.m_title.SetTextSize(this.m_textSize);
            this.m_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
            this.m_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
            this.m_title.SetText(param1);
            addChild(this.m_title);
            if(this.m_isFitText == true)
            {
               this.ResizeWindowSize();
            }
            else
            {
               this.CalcTextPos();
            }
         }
      }
      
      public function SetVisibleWindow(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function SetVisibleWindow2(param1:Boolean) : *
      {
         this.m_win.smb_win00.visible = param1;
      }
      
      public function SetLine(param1:int) : *
      {
         this.m_line_num = param1;
      }
      
      public function GetSelectValue() : int
      {
         return int(this.GetSelValue());
      }
      
      public function GetWindowWidth() : int
      {
         return this.m_win.smb_win00.width;
      }
      
      public function GetWindowHeight() : int
      {
         return this.m_win.smb_win00.height;
      }
      
      public function AddWindowPostion(param1:Number, param2:Number) : *
      {
         this.x += param1;
         this.y += param2;
      }
      
      private function SetMenu(param1:Array, param2:Boolean) : *
      {
         var _loc3_:* = 0;
         var _loc4_:String = null;
         this.m_menuArr = param1.concat();
         this.m_isMsgId = param2;
         this.m_maxWidth = 0;
         _loc3_ = 0;
         while(_loc3_ < this.m_menuNum)
         {
            if(this.m_dispMenuArr[_loc3_] == null)
            {
               this.m_dispMenuArr[_loc3_] = new smb_font();
               addChild(this.m_dispMenuArr[_loc3_]);
            }
            _loc4_ = param1[_loc3_];
            if(this.m_isDispSel == true)
            {
               _loc4_ = param1[this.GetDispNo() + _loc3_];
            }
            if(param2 == true)
            {
               _loc4_ = String(ExternalInterface.call("MessageConvert",_loc4_));
            }
            this.m_dispMenuArr[_loc3_].SetTextAutoSize();
            this.m_dispMenuArr[_loc3_].SetTextColor(this.m_textColor);
            this.m_dispMenuArr[_loc3_].SetTextSize(this.m_textSize);
            this.m_dispMenuArr[_loc3_].SetTextPivot(smb_font.CCD_PIVOT_CC);
            this.m_dispMenuArr[_loc3_].SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
            this.m_dispMenuArr[_loc3_].SetText(_loc4_);
            if(this.m_dispMenuArr[_loc3_].width > this.m_maxWidth)
            {
               this.m_maxWidth = this.m_dispMenuArr[_loc3_].width;
            }
            _loc3_++;
         }
         if(this.m_dispMenuArr.length > this.m_menuNum)
         {
            this.m_dispMenuArr.length - 1;
            while(_loc3_ < this.m_menuNum)
            {
               removeChild(this.m_dispMenuArr[_loc3_]);
               this.m_dispMenuArr[_loc3_] = null;
               _loc3_--;
            }
            this.m_dispMenuArr.length = this.m_menuNum;
         }
         this.m_cursor.width = this.m_maxWidth + CCD_CURSOR_MARGIN_X * 2;
         if(this.m_isFitText == true)
         {
            this.ResizeWindowSize();
         }
         else
         {
            this.CalcTextPos();
         }
      }
      
      private function ScrollMsg(param1:int) : *
      {
         var _loc2_:int = 0;
         var _loc3_:String = null;
         if(param1 != this.GetDispNo())
         {
            _loc2_ = 0;
            while(_loc2_ < this.m_menuNum)
            {
               _loc3_ = this.m_menuArr[this.GetDispNo() + _loc2_];
               if(this.m_isMsgId == true)
               {
                  _loc3_ = String(ExternalInterface.call("MessageConvert",_loc3_));
               }
               this.m_dispMenuArr[_loc2_].SetText(_loc3_);
               _loc2_++;
            }
         }
      }
      
      public function VisibleTextCursor(param1:Boolean) : *
      {
         var _loc2_:int = 0;
         _loc2_ = 0;
         while(_loc2_ < this.m_dispMenuArr.length)
         {
            this.m_dispMenuArr[_loc2_].visible = param1;
            _loc2_++;
         }
         this.m_cursor.visible = param1;
         if(this.m_title != null)
         {
            this.m_title.visible = param1;
         }
         if(this.m_line_num >= 0)
         {
            this.m_line.visible = param1;
         }
      }
      
      private function CalcTextPos() : *
      {
         var _loc6_:Number = NaN;
         var _loc1_:uint = this.m_dispMenuArr.length;
         var _loc2_:Number = Number(this.m_win.smb_win00.y);
         var _loc3_:int = 0;
         var _loc4_:Number = 0;
         _loc3_ = 0;
         while(_loc3_ < _loc1_)
         {
            _loc4_ += this.m_dispMenuArr[_loc3_].GetSymbolHeight();
            _loc3_++;
         }
         if(this.m_title != null)
         {
            _loc2_ -= (_loc4_ + this.m_textLeader * (_loc1_ - 1) + this.m_title.GetTextFieldHeight() + CCD_TITLE_MARGIN_Y) / 2;
            _loc2_ += this.m_title.GetTextFieldHeight() / 2;
            this.m_title.SetTextPos(this.m_win.smb_win00.x,_loc2_);
            _loc2_ += this.m_title.GetTextFieldHeight() / 2 + CCD_TITLE_MARGIN_Y;
         }
         else
         {
            _loc2_ -= (_loc4_ + this.m_textLeader * (_loc1_ - 1)) / 2;
         }
         trace("menuTop:" + _loc2_);
         var _loc5_:Number = 0;
         _loc3_ = 0;
         while(_loc3_ < _loc1_)
         {
            if(this.m_line_num >= 0 && this.m_line_num == _loc3_)
            {
               _loc5_ += 8;
               this.m_line.y = _loc2_ + _loc5_ + this.m_textLeader * _loc3_ + _loc6_;
               _loc5_ += 8;
            }
            _loc5_ += this.m_dispMenuArr[_loc3_].GetSymbolHeight() / 2;
            _loc6_ = this.m_dispMenuArr[_loc3_].GetRubyTextHeight() / 2;
            this.m_dispMenuArr[_loc3_].SetTextPos(this.m_win.smb_win00.x,_loc2_ + _loc5_ + this.m_textLeader * _loc3_ + _loc6_);
            trace("menuPosY:" + (_loc2_ + _loc5_ + this.m_textLeader * _loc3_ + _loc6_));
            _loc5_ += this.m_dispMenuArr[_loc3_].GetSymbolHeight() / 2;
            _loc3_++;
         }
         this.m_line.width = this.m_maxWidth + 60;
      }
   }
}

