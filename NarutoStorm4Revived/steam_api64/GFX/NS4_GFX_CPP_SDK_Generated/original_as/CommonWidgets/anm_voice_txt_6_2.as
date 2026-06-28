package net_top_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class anm_voice_txt_6 extends MovieClip
   {
      
      public var txt_voice:smb_font;
      
      public function anm_voice_txt_6()
      {
         super();
         addFrameScript(0,this.frame1,7,this.frame8,11,this.frame12);
      }
      
      internal function frame1() : *
      {
         this.txt_voice.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_voice.SetTextSize(28);
         this.txt_voice.SetTextFieldWidth(1000);
         this.txt_voice.SetTextWordWrap(true);
      }
      
      internal function frame8() : *
      {
         stop();
      }
      
      internal function frame12() : *
      {
         stop();
      }
   }
}

