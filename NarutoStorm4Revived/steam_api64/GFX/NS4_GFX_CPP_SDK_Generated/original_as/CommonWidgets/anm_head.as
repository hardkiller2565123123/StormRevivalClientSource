package script.shop_list
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class anm_head extends MovieClip
   {
      
      internal static const CCD_ITEM_OWN_MARGIN_X:Number = 70;
      
      public var txt_head_name:smb_font;
      
      public var txt_head_num:smb_font;
      
      public var txt_head_own:smb_font;
      
      public var txt_head_price:smb_font;
      
      private var m_txtName:smb_font = null;
      
      private var m_txtPrice:smb_font = null;
      
      private var m_txtNum:smb_font = null;
      
      private var m_txtOwn:smb_font = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function anm_head()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtName = this["txt_head_name"];
         this.m_txtPrice = this["txt_head_price"];
         this.m_txtNum = this["txt_head_num"];
         this.m_txtOwn = this["txt_head_own"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         var _loc2_:Point = null;
         var _loc3_:Number = NaN;
         var _loc4_:Number = NaN;
         if(this.m_txtName.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = new Point();
               _loc2_ = new Point();
               this.m_txtName.GetTextPos(_loc1_);
               this.m_txtOwn.GetTextPos(_loc2_);
               trace("ChangedLayout:","name:" + _loc1_,"Own:" + _loc2_);
               this.m_txtName.SetTextPos(_loc2_.x,_loc2_.y);
               _loc3_ = _loc2_.x;
               this.m_txtOwn.SetTextPos(_loc1_.x + CCD_ITEM_OWN_MARGIN_X,_loc1_.y);
               this.m_txtNum.GetTextPos(_loc2_);
               _loc4_ = Math.abs(_loc2_.x - _loc3_) + CCD_ITEM_OWN_MARGIN_X;
               this.m_txtNum.SetTextPos(_loc1_.x + _loc4_,_loc1_.y);
               this.m_txtPrice.GetTextPos(_loc2_);
               _loc4_ = Math.abs(_loc2_.x - _loc3_) + CCD_ITEM_OWN_MARGIN_X;
               this.m_txtPrice.SetTextPos(_loc1_.x + _loc4_,_loc1_.y);
            }
            this.m_txtName.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtName.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtPrice.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtPrice.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_txtNum.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtOwn.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head_name.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head_name.SetTextColor(16777215);
         this.txt_head_name.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_name.SetTextSize(30);
         this.txt_head_price.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_head_price.SetTextSize(30);
         this.txt_head_price.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head_num.SetTextSize(30);
         this.txt_head_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_num.SetTextFieldWidth(140);
         this.txt_head_num.SetTextFit(true);
         this.txt_head_own.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head_own.SetTextSize(30);
         this.txt_head_own.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_own.SetTextFieldWidth(140);
         this.txt_head_own.SetTextFit(true);
         this.CheckArabicLayout();
      }
   }
}

