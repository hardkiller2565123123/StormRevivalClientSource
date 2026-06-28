package result_net_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class smb_ru_plate_10 extends MovieClip
   {
      
      public var mc_arrow:MovieClip;
      
      public var txt_ru_next:smb_font;
      
      public var txt_ru_current:smb_font;
      
      public function smb_ru_plate_10()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_ru_next.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ru_next.SetTextColor(smb_font.CCD_COLOR_RED);
         this.txt_ru_next.SetDropShadowFilter(11645361);
         this.txt_ru_next.SetTextFieldWidth(536);
         this.txt_ru_next.SetTextFit(true);
         this.txt_ru_current.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ru_current.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ru_current.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ru_current.SetTextFieldWidth(536);
         this.txt_ru_current.SetTextFit(true);
      }
   }
}

