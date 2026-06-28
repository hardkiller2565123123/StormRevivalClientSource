package script.cutin_rcvry
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcp_frame_bar1.smb_frame_bar1_3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_recvry_txt extends MovieClip
   {
      
      public var mc_base:smb_frame_bar1_3;
      
      public var txt_recvry00:smb_font;
      
      public var txt_recvry_per:smb_font;
      
      private var m_txtRecvry:smb_font = null;
      
      private var m_txtPer:smb_font = null;
      
      private var m_base:MovieClip = null;
      
      public function nut_recvry_txt()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtRecvry = this["txt_recvry00"];
         this.m_txtPer = this["txt_recvry_per"];
         this.m_base = this["mc_base"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_txtRecvry.IsArabic() == true)
         {
            this.m_base.scaleX *= -1;
            _loc1_ = new Point();
            this.m_txtRecvry.GetTextPos(_loc1_);
            this.m_txtRecvry.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtPer.GetTextPos(_loc1_);
            this.m_txtPer.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_txtRecvry.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtRecvry.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtPer.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtPer.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
      }
      
      internal function frame1() : *
      {
         this.txt_recvry00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_recvry00.SetTextColor(16774492);
         this.txt_recvry00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_recvry_per.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_recvry_per.SetTextColor(16774492);
         this.txt_recvry_per.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.CheckArabicLayout();
      }
   }
}

