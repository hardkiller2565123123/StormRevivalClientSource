package script.cutin_rcvry
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcp_frame_bar1.smb_frame_bar1_1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public class nut_resultbar00 extends MovieClip
   {
      
      public var mc_base:smb_frame_bar1_1;
      
      public var txt_per00:smb_font;
      
      public var txt_rank00:smb_font;
      
      public var txt_title00:smb_font;
      
      private var m_txtTitle:smb_font = null;
      
      private var m_txtRank:smb_font = null;
      
      private var m_txtPer:smb_font = null;
      
      private var m_base:MovieClip = null;
      
      public function nut_resultbar00()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtTitle = this["txt_title00"];
         this.m_txtRank = this["txt_rank00"];
         this.m_txtPer = this["txt_per00"];
         this.m_base = this["mc_base"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_txtTitle.IsArabic() == true)
         {
            this.m_base.scaleX *= -1;
            _loc1_ = new Point();
            this.m_txtTitle.GetTextPos(_loc1_);
            this.m_txtTitle.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtRank.GetTextPos(_loc1_);
            this.m_txtRank.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtPer.GetTextPos(_loc1_);
            this.m_txtPer.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtTitle.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtTitle.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtRank.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtRank.SetTextPivot(smb_font.CCD_PIVOT_CC);
            this.m_txtPer.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtPer.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
      }
      
      internal function frame1() : *
      {
         this.txt_title00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rank00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rank00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_per00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_per00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.CheckArabicLayout();
      }
   }
}

