package script.freebtl_leag
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public dynamic class nut_list_total_00 extends MovieClip
   {
      
      public var txt_score:smb_font;
      
      public function nut_list_total_00()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_score.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_score.SetTextSize(47);
         this.txt_score.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_score.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
      }
   }
}

