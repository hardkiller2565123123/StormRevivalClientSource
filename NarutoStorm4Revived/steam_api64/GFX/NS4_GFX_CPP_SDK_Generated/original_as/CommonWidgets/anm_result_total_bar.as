package script.result_main
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class anm_result_total_bar extends MovieClip
   {
      
      public var txt_total:smb_font;
      
      public var txt_total_money:smb_font;
      
      public var txt_total_ryo:smb_font;
      
      internal var m_txtTotal:smb_font = null;
      
      internal var m_txtMoney:smb_font = null;
      
      internal var m_txtRyo:smb_font = null;
      
      internal var m_isChangedLayout:Boolean = false;
      
      public function anm_result_total_bar()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtTotal = this["txt_total"];
         this.m_txtMoney = this["txt_total_money"];
         this.m_txtRyo = this["txt_total_ryo"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_isChangedLayout == true)
         {
            return;
         }
         if(this.m_txtTotal.IsArabic() == true)
         {
            _loc1_ = new Point();
            this.m_txtTotal.GetTextPos(_loc1_);
            this.m_txtTotal.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtTotal.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtTotal.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_txtMoney.GetTextPos(_loc1_);
            this.m_txtMoney.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtMoney.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtMoney.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_txtRyo.GetTextPos(_loc1_);
            this.m_txtRyo.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtRyo.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtRyo.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_total.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_total.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
         this.txt_total_money.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total_money.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_total_money.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
         this.txt_total_ryo.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_total_ryo.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_total_ryo.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
         this.CheckArabicLayout();
      }
   }
}

