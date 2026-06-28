package script.shop_cmn
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class nut_total extends MovieClip
   {
      
      internal static const CCD_LAYOUT_ALIGN_LEFT:int = 0;
      
      internal static const CCD_LAYOUT_ALIGN_RIGHT:int = 1;
      
      public var txt_price:smb_font;
      
      public var txt_total:smb_font;
      
      private var m_txtTotal:smb_font = null;
      
      private var m_txtPrice:smb_font = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      private var m_layoutAlign:int = 0;
      
      public function nut_total()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtTotal = this["txt_total"];
         this.m_txtPrice = this["txt_price"];
      }
      
      public function SetArabicLayoutRight() : *
      {
         this.m_txtTotal.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.m_txtPrice.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.m_layoutAlign = CCD_LAYOUT_ALIGN_RIGHT;
      }
      
      public function SetArabicLayoutLeft() : *
      {
         this.m_txtTotal.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.m_txtPrice.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.m_layoutAlign = CCD_LAYOUT_ALIGN_LEFT;
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         var _loc2_:Point = null;
         if(this.m_txtTotal.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = new Point();
               _loc2_ = new Point();
               this.m_txtTotal.GetTextPos(_loc1_);
               this.m_txtPrice.GetTextPos(_loc2_);
               this.m_txtTotal.SetTextPos(_loc2_.x,_loc1_.y);
               this.m_txtPrice.SetTextPos(_loc1_.x,_loc2_.y);
            }
            this.m_txtTotal.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtPrice.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            if(this.m_layoutAlign == CCD_LAYOUT_ALIGN_LEFT)
            {
               this.SetArabicLayoutLeft();
            }
            else
            {
               this.SetArabicLayoutRight();
            }
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_total.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_total.SetTextSize(40);
         this.txt_price.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_price.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_price.SetTextSize(40);
         this.CheckArabicLayout();
      }
   }
}

