package map_l_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol30")]
   public dynamic class nut_frm_11 extends MovieClip
   {
      
      public var txt_area:smb_font;
      
      public var txt_msg:smb_font;
      
      public function nut_frm_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_area.SetTextSize(31);
         this.txt_area.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_area.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_msg.SetTextSize(31);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_CT);
         this.txt_msg.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

