package script.xcmn_font
{
   import flash.display.BlendMode;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.filters.BitmapFilterQuality;
   import flash.filters.DropShadowFilter;
   import flash.geom.Point;
   
   public class smb_font extends MovieClip
   {
      
      public static const CCD_COLOR_RED:uint = smb_font2.CCD_COLOR_RED;
      
      public static const CCD_COLOR_GREEN:uint = smb_font2.CCD_COLOR_GREEN;
      
      public static const CCD_COLOR_BLUE:uint = smb_font2.CCD_COLOR_BLUE;
      
      public static const CCD_COLOR_WHITE:uint = smb_font2.CCD_COLOR_WHITE;
      
      public static const CCD_COLOR_BLACK:uint = smb_font2.CCD_COLOR_BLACK;
      
      public static const CCD_FONT_SIZE_SMALL:uint = smb_font2.CCD_FONT_SIZE_SMALL;
      
      public static const CCD_FONT_SIZE_MIDDLE:uint = smb_font2.CCD_FONT_SIZE_MIDDLE;
      
      public static const CCD_FONT_SIZE_LARGE:uint = smb_font2.CCD_FONT_SIZE_LARGE;
      
      public static const CCD_PIVOT_LT:uint = smb_font2.CCD_PIVOT_LT;
      
      public static const CCD_PIVOT_LC:uint = smb_font2.CCD_PIVOT_LC;
      
      public static const CCD_PIVOT_LB:uint = smb_font2.CCD_PIVOT_LB;
      
      public static const CCD_PIVOT_CT:uint = smb_font2.CCD_PIVOT_CT;
      
      public static const CCD_PIVOT_CC:uint = smb_font2.CCD_PIVOT_CC;
      
      public static const CCD_PIVOT_CB:uint = smb_font2.CCD_PIVOT_CB;
      
      public static const CCD_PIVOT_RT:uint = smb_font2.CCD_PIVOT_RT;
      
      public static const CCD_PIVOT_RC:uint = smb_font2.CCD_PIVOT_RC;
      
      public static const CCD_PIVOT_RB:uint = smb_font2.CCD_PIVOT_RB;
      
      public static const CCD_ALIGN_LEFT:String = smb_font2.CCD_ALIGN_LEFT;
      
      public static const CCD_ALIGN_CENTER:String = smb_font2.CCD_ALIGN_CENTER;
      
      public static const CCD_ALIGN_RIGHT:String = smb_font2.CCD_ALIGN_RIGHT;
      
      private static const CCD_MIN_FIT_SCALE:Number = 0.01;
      
      private var m_fontCore:smb_font2 = null;
      
      private var m_iconBtnArr:Array = new Array();
      
      private var m_ltPos:Point = new Point(x,y);
      
      private var m_pivot:int = CCD_PIVOT_LT;
      
      private var m_isFitFont:Boolean = false;
      
      private var m_fixedWidth:Number = 0;
      
      public function smb_font()
      {
         super();
         this.m_fontCore = this["mc_font2"];
         var _loc1_:MovieClip = this["dmy_icon"];
         removeChild(_loc1_);
         var _loc2_:MovieClip = this["dmy_txt"];
         removeChild(_loc2_);
         this.m_ltPos.x = x;
         this.m_ltPos.y = y;
         this.m_fixedWidth = width;
         addEventListener(Event.REMOVED_FROM_STAGE,this.Removed);
      }
      
      public function Removed(param1:Event) : *
      {
         var _loc2_:int = 0;
         _loc2_ = 0;
         while(_loc2_ < this.m_iconBtnArr.length)
         {
            removeChild(this.m_iconBtnArr[_loc2_]);
            _loc2_++;
         }
         this.m_iconBtnArr.length = 0;
      }
      
      public function SetText(param1:String) : *
      {
         this.m_fontCore.blendMode = BlendMode.LAYER;
         this.m_fontCore.SetText(param1);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
         this.CalcPivotPos();
         this.CreateIcon();
         this.CalcIconPos();
      }
      
      public function SetTextColor(param1:uint) : *
      {
         this.m_fontCore.SetTextColor(param1);
      }
      
      public function SetTextLineColor(param1:uint, param2:uint) : *
      {
         this.m_fontCore.SetTextLineColor(param1,param2);
      }
      
      public function SetTextAlign(param1:String) : *
      {
         this.m_fontCore.SetTextAlign(param1);
         this.CalcPivotPos();
         this.CalcIconPos();
      }
      
      public function SetTextSize(param1:uint) : *
      {
         this.m_fontCore.SetTextSize(param1);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
         this.CalcPivotPos();
      }
      
      public function SetTextWordWrap(param1:Boolean) : *
      {
         this.m_fontCore.SetTextWordWrap(param1,this.m_fixedWidth);
         if(param1 == true)
         {
            this.SetTextFit(false);
         }
         else
         {
            this.CalcPivotPos();
            this.CalcIconPos();
         }
      }
      
      public function SetTextFieldWidth(param1:Number) : *
      {
         this.m_fixedWidth = param1;
         this.m_fontCore.SetTextFieldWidth(param1);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
         this.CalcPivotPos();
         this.CalcIconPos();
      }
      
      public function SetTextPivot(param1:uint) : *
      {
         this.m_pivot = param1;
         this.CalcPivotPos();
      }
      
      public function SetTextPos(param1:Number, param2:Number) : *
      {
         this.m_ltPos.x = param1;
         this.m_ltPos.y = param2;
         this.CalcPivotPos();
      }
      
      public function SetOffsetPos(param1:Number, param2:Number) : *
      {
         this.m_ltPos.x += param1;
         this.m_ltPos.y += param2;
         this.CalcPivotPos();
      }
      
      public function SetTextFit(param1:Boolean) : *
      {
         this.m_isFitFont = param1;
         if(this.m_isFitFont == true)
         {
            this.SetTextWordWrap(false);
            this.CalcFitFont();
         }
         else
         {
            scaleX = 1;
         }
         this.CalcPivotPos();
         this.CalcIconPos();
      }
      
      public function SetTextAutoSize() : *
      {
         this.SetTextFit(false);
         this.m_fontCore.SetTextWordWrap(false,this.m_fixedWidth);
      }
      
      public function SetDropShadowFilter(param1:uint) : *
      {
         var _loc2_:DropShadowFilter = new DropShadowFilter();
         _loc2_.distance = 5;
         _loc2_.angle = 45;
         _loc2_.color = param1;
         _loc2_.alpha = 0.95;
         _loc2_.blurX = 4;
         _loc2_.blurY = 4;
         _loc2_.strength = 1;
         _loc2_.quality = BitmapFilterQuality.LOW;
         _loc2_.inner = false;
         _loc2_.knockout = false;
         _loc2_.hideObject = false;
         this.filters = [_loc2_];
      }
      
      public function DisableDropShadowFilter() : *
      {
         this.filters = [];
      }
      
      public function SetTextRubyEnable(param1:Boolean) : *
      {
         this.m_fontCore.SetTextRubyEnable(param1);
         this.CalcPivotPos();
      }
      
      public function ReplaceTextList(param1:Array) : *
      {
         this.m_fontCore.ReplaceTextList(param1);
         this.CalcPivotPos();
         this.CalcIconPos();
      }
      
      public function GetTextFieldWidth() : Number
      {
         return this.m_fontCore.GetTextFieldWidth();
      }
      
      public function GetTextFieldHeight() : Number
      {
         return this.m_fontCore.GetTextFieldHeight();
      }
      
      public function GetSymbolHeight() : Number
      {
         return this.m_fontCore.GetSymbolHeight();
      }
      
      public function GetRubyTextHeight() : Number
      {
         return this.m_fontCore.GetRubyTextHeight();
      }
      
      public function GetTextNumlines() : int
      {
         return this.m_fontCore.GetTextNumlines();
      }
      
      public function GetTextLineY(param1:int) : Number
      {
         return this.m_fontCore.GetTextLineY(param1) + y;
      }
      
      public function GetTextPos(param1:Point) : *
      {
         param1.x = this.m_ltPos.x;
         param1.y = this.m_ltPos.y;
      }
      
      public function GetTextSize() : uint
      {
         return this.m_fontCore.GetTextSize();
      }
      
      public function GetTextColor() : uint
      {
         return this.m_fontCore.GetTextColor();
      }
      
      public function SetPlayerSide(param1:int) : *
      {
         this.m_fontCore.SetPlayerSide(param1);
      }
      
      public function IsWordWrap() : Boolean
      {
         return this.m_fontCore.IsWordWrap();
      }
      
      private function CalcFitFont() : *
      {
         this.width /= this.scaleX;
         this.scaleX = this.m_fixedWidth / this.width;
         if(this.scaleX > 1)
         {
            this.scaleX = 1;
         }
         else if(this.scaleX < CCD_MIN_FIT_SCALE)
         {
            this.scaleX = CCD_MIN_FIT_SCALE;
            trace("****smb_font.CalcFitFont[FIT処理で下限を超えてしまいました]****");
         }
      }
      
      private function CreateIcon() : *
      {
         this.m_fontCore.CreateIcon(this,this.m_iconBtnArr);
      }
      
      private function CalcIconPos() : *
      {
         this.m_fontCore.CalcIconPos(this,this.m_iconBtnArr);
      }
      
      private function CalcPivotPos() : *
      {
         this.m_fontCore.blendMode = BlendMode.LAYER;
         var _loc1_:Point = new Point(0,0);
         if(this.m_pivot & FontParam.CCD_PIVOT_H_CENTER)
         {
            _loc1_.x = -width / 2;
         }
         else if(this.m_pivot & FontParam.CCD_PIVOT_H_RIGHT)
         {
            _loc1_.x = -width;
         }
         if(this.m_pivot & FontParam.CCD_PIVOT_V_CENTER)
         {
            _loc1_.y = -this.m_fontCore.GetTextFieldHeight() / 2;
         }
         else if(this.m_pivot & FontParam.CCD_PIVOT_V_BOTTOM)
         {
            _loc1_.y = -this.m_fontCore.GetTextFieldHeight();
         }
         x = this.m_ltPos.x + _loc1_.x;
         y = this.m_ltPos.y + _loc1_.y;
         this.m_fontCore.ResetRuby();
      }
      
      public function SetTextBorder(param1:Boolean) : *
      {
         this.m_fontCore.SetTextBorder(param1);
      }
      
      public function SetTextBorderColor(param1:uint) : *
      {
         this.m_fontCore.SetTextBorderColor(param1);
      }
      
      public function GetFontCoreHeight() : Number
      {
         return this.m_fontCore.height;
      }
      
      public function GetText() : String
      {
         return this.m_fontCore.GetText();
      }
   }
}

