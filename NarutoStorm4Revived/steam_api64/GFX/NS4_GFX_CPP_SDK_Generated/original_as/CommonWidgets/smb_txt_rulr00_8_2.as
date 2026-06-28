package freebtl_rlt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public dynamic class smb_txt_rulr00_8 extends MovieClip
   {
      
      public var txt_rulr00:smb_font;
      
      public function smb_txt_rulr00_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rulr00.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_rulr00.SetTextSize(33);
         if(this.txt_rulr00.IsArabic() == true)
         {
            this.txt_rulr00.SetTextFieldWidth(930);
            this.txt_rulr00.SetOffsetPos(930,0);
            this.txt_rulr00.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_rulr00.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_rulr00.SetTextFieldWidth(1040);
            this.txt_rulr00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_rulr00.SetTextFit(true);
      }
   }
}

