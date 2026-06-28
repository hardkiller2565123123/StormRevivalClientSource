package freebtl_rlt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class smb_txt_rulr01_7 extends MovieClip
   {
      
      public var txt_rulr01:smb_font;
      
      public function smb_txt_rulr01_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rulr01.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_rulr01.SetTextSize(33);
         if(this.txt_rulr01.IsArabic() == true)
         {
            this.txt_rulr01.SetTextFieldWidth(930);
            this.txt_rulr01.SetOffsetPos(930,0);
            this.txt_rulr01.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_rulr01.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_rulr01.SetTextFieldWidth(1040);
            this.txt_rulr01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_rulr01.SetTextFit(true);
      }
   }
}

