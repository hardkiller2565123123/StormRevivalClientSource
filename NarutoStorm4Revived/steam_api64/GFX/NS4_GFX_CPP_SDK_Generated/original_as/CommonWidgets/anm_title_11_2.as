package map_sm_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol71")]
   public dynamic class anm_title_11 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function anm_title_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextFieldWidth(750);
         this.txt_title.SetTextFit(true);
      }
   }
}

