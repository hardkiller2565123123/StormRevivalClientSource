package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol36")]
   public dynamic class smb_tit_4 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function smb_tit_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
   }
}

