package script.xcmn_font
{
   import flash.display.Bitmap;
   import flash.display.BitmapData;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.geom.Matrix;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class anm_font extends MovieClip
   {
      
      private static const CCD_MIN_FIT_SCALE:Number = 0.01;
      
      public var dmy_icon:all_btn_plat;
      
      public var dmy_txt:anm_icon;
      
      public var mc_font2:smb_font2;
      
      private var m_fontCore:smb_font2 = null;
      
      private var m_txtBmp:Bitmap = null;
      
      private var m_iconBtnArr:Array = new Array();
      
      private var m_fixedWidth:Number = 0;
      
      private var m_text:String = "w";
      
      private var m_replaceTextCtn:Array = new Array();
      
      private var m_shadowCol:uint = 0;
      
      private var m_isFitFont:Boolean = false;
      
      private var m_isShadowDrop:Boolean = false;
      
      private var m_isChangeBmp:Boolean = false;
      
      public function anm_font()
      {
         super();
         this.cacheAsBitmap = false;
         this.m_fontCore = this["mc_font2"];
         var _loc1_:MovieClip = this["dmy_icon"];
         this.removeChild(_loc1_);
         var _loc2_:MovieClip = this["dmy_txt"];
         this.removeChild(_loc2_);
         this.m_fixedWidth = width;
         addEventListener(Event.REMOVED_FROM_STAGE,this.Removed);
      }
      
      public function Removed(param1:Event) : *
      {
         var _loc2_:int = 0;
         _loc2_ = 0;
         while(_loc2_ < this.m_iconBtnArr.length)
         {
            this.removeChild(this.m_iconBtnArr[_loc2_]);
            _loc2_++;
         }
         this.m_iconBtnArr.length = 0;
         this.DeleteBitmap();
      }
      
      public function ChangeBitmapDraw() : *
      {
         if(this.m_isChangeBmp == false)
         {
            this.m_isChangeBmp = true;
            this.ChangeDrawMode(true);
         }
      }
      
      public function ChangeTextFieldDraw() : *
      {
         if(this.m_isChangeBmp == true)
         {
            this.ChangeDrawMode(false);
            this.m_isChangeBmp = false;
         }
      }
      
      public function UpdateBitmap() : *
      {
         if(this.m_isChangeBmp == true)
         {
            this.CreateBitmap();
         }
      }
      
      public function SetText(param1:String, param2:Array) : *
      {
         this.m_text = param1;
         this.m_fontCore.SetText(param1,param2);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
         this.CreateIcon();
         this.CalcIconPos();
         if(this.m_isChangeBmp == true)
         {
            this.CreateBitmap();
         }
      }
      
      public function SetTextColor(param1:uint) : *
      {
         this.m_fontCore.SetTextColor(param1);
         var _loc2_:int = 0;
         while(_loc2_ < this.m_iconBtnArr.length)
         {
            if(this.m_iconBtnArr[_loc2_] != undefined && this.m_iconBtnArr[_loc2_].name.indexOf("txt") != -1)
            {
               this.m_iconBtnArr[_loc2_].SetTexiIconColor(param1);
            }
            _loc2_++;
         }
      }
      
      public function SetTextLineColor(param1:uint, param2:uint) : *
      {
         this.m_fontCore.SetTextLineColor(param1,param2);
      }
      
      public function SetTextAlign(param1:String) : *
      {
         this.m_fontCore.SetTextAlign(param1);
         this.CalcIconPos();
      }
      
      public function SetTextSize(param1:uint) : *
      {
         this.m_fontCore.SetTextSize(param1);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
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
            this.CalcIconPos();
         }
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
         this.CalcIconPos();
      }
      
      public function SetTextAutoSize() : *
      {
         this.SetTextFit(false);
         this.m_fontCore.SetTextWordWrap(false,this.m_fixedWidth);
      }
      
      public function SetDropShadowFilter(param1:uint) : *
      {
         this.m_fontCore.SetDropShadowFilter(param1);
         var _loc2_:int = 0;
         while(_loc2_ < this.m_iconBtnArr.length)
         {
            if(this.m_iconBtnArr[_loc2_].name.indexOf("txtIcon") != -1)
            {
               this.m_iconBtnArr[_loc2_].SetEnableShadow(param1);
            }
            _loc2_++;
         }
         this.m_shadowCol = param1;
         this.m_isShadowDrop = true;
         if(this.IsArabic() == true)
         {
            this.CalcIconPos();
         }
      }
      
      public function DisableDropShadowFilter() : *
      {
         this.m_fontCore.DisableDropShadowFilter();
         this.m_isShadowDrop = false;
      }
      
      public function SetTextRubyEnable(param1:Boolean) : *
      {
         this.m_fontCore.SetTextRubyEnable(param1);
      }
      
      public function SetPlayerSide(param1:int) : *
      {
         this.m_fontCore.SetPlayerSide(param1);
      }
      
      public function SetEnableIconTag(param1:Boolean) : *
      {
         this.m_fontCore.SetEnableIconTag(param1);
      }
      
      public function ReplaceTextList(param1:Array) : *
      {
         this.m_fontCore.ReplaceTextList(param1);
         if(this.m_isFitFont == true)
         {
            this.CalcFitFont();
         }
         this.CalcIconPos();
         this.m_replaceTextCtn.length = 0;
         var _loc2_:* = 0;
         while(_loc2_ < param1.length)
         {
            this.m_replaceTextCtn[_loc2_] = param1[_loc2_];
            _loc2_++;
         }
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
      
      public function GetTextSize() : uint
      {
         return this.m_fontCore.GetTextSize();
      }
      
      public function GetTextColor() : uint
      {
         return this.m_fontCore.GetTextColor();
      }
      
      public function GetTextWidthEnableWordWrap() : Number
      {
         return this.m_fontCore.GetTextWidthEnableWordWrap();
      }
      
      public function IsWordWrap() : Boolean
      {
         return this.m_fontCore.IsWordWrap();
      }
      
      public function IsArabic() : Boolean
      {
         return this.m_fontCore.IsArabic();
      }
      
      public function DuplicationFontSymbol() : anm_font
      {
         var _loc1_:anm_font = new anm_font();
         _loc1_.x = x;
         _loc1_.y = y;
         _loc1_.scaleX = scaleX;
         _loc1_.scaleY = scaleY;
         _loc1_.SetTextSize(this.m_fontCore.GetTextSize());
         _loc1_.SetTextColor(this.m_fontCore.GetTextColor());
         _loc1_.SetPlayerSide(this.m_fontCore.GetPlayerSide());
         _loc1_.SetTextAlign(this.m_fontCore.GetTextAlign());
         _loc1_.SetTextRubyEnable(this.m_fontCore.IsRubyEnable());
         _loc1_.SetText(this.m_text,null);
         _loc1_.ReplaceTextList(this.m_replaceTextCtn);
         if(this.m_isShadowDrop == true)
         {
            _loc1_.SetDropShadowFilter(this.m_shadowCol);
         }
         if(this.m_isChangeBmp == true)
         {
            _loc1_.ChangeBitmapDraw();
         }
         return _loc1_;
      }
      
      public function ResetRuby() : *
      {
         this.m_fontCore.ResetRuby();
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
      
      private function CreateBitmap() : *
      {
         var _loc1_:Boolean = false;
         this.DeleteBitmap();
         _loc1_ = parent.visible;
         parent.visible = true;
         var _loc2_:Boolean = this.m_fontCore.visible;
         this.m_fontCore.visible = true;
         var _loc3_:Array = new Array();
         var _loc4_:int = 0;
         while(_loc4_ < this.m_iconBtnArr.length)
         {
            _loc3_.push(this.m_iconBtnArr[_loc4_].visible);
            this.m_iconBtnArr[_loc4_].visible = true;
            _loc4_++;
         }
         var _loc5_:Number = this.scaleX;
         this.scaleX = 1;
         var _loc6_:BitmapData = new BitmapData(this.width,this.height,true,0);
         this.m_txtBmp = new Bitmap();
         var _loc7_:Matrix = new Matrix();
         _loc7_.translate(-getRect(this).x,-getRect(this).y);
         _loc6_.draw(this,_loc7_);
         this.m_txtBmp.bitmapData = _loc6_;
         addChild(this.m_txtBmp);
         this.scaleX = _loc5_;
         parent.visible = _loc1_;
         this.m_fontCore.visible = _loc2_;
         _loc4_ = 0;
         while(_loc4_ < this.m_iconBtnArr.length)
         {
            this.m_iconBtnArr[_loc4_].visible = _loc3_[_loc4_];
            _loc4_++;
         }
      }
      
      private function DeleteBitmap() : *
      {
         if(this.m_txtBmp != null)
         {
            removeChild(this.m_txtBmp);
            this.m_txtBmp = null;
         }
      }
      
      private function ChangeDrawMode(param1:Boolean) : *
      {
         var _loc2_:int = 0;
         if(param1 == true)
         {
            this.CreateBitmap();
            this.m_fontCore.visible = false;
            _loc2_ = 0;
            while(_loc2_ < this.m_iconBtnArr.length)
            {
               this.m_iconBtnArr[_loc2_].visible = false;
               _loc2_++;
            }
         }
         else
         {
            this.DeleteBitmap();
            this.m_fontCore.visible = true;
            _loc2_ = 0;
            while(_loc2_ < this.m_iconBtnArr.length)
            {
               this.m_iconBtnArr[_loc2_].visible = true;
               _loc2_++;
            }
         }
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

