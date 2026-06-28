package cutin_match_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class anm_txt_3 extends MovieClip
   {
      
      public var txt_cutin:smb_font;
      
      public function anm_txt_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_cutin.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cutin.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cutin.SetTextSize(84);
      }
   }
}

