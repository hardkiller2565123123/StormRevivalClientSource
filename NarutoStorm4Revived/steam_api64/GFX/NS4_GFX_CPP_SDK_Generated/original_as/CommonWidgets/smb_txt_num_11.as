package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol27")]
   public dynamic class smb_txt_num_11 extends MovieClip
   {
      
      public var txt_num:smb_font;
      
      public function smb_txt_num_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         if(this.txt_num.IsArabic() == true)
         {
            this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.txt_num.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         this.txt_num.SetTextSize(30);
         this.txt_num.SetTextFieldWidth(1300);
         this.txt_num.SetTextFit(true);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

