package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol47")]
   public dynamic class anm_cond_24 extends MovieClip
   {
      
      public var txt_cond1:smb_font;
      
      public var txt_cond2:smb_font;
      
      public var txt_cond3:smb_font;
      
      public var txt_head:smb_font;
      
      public function anm_cond_24()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head.SetText("バトル条件");
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_head.SetTextSize(29);
         this.txt_head.SetTextFieldWidth(800);
         this.txt_head.SetTextFit(true);
         this.txt_cond1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond1.SetTextColor(4467231);
         this.txt_cond1.SetTextSize(29);
         this.txt_cond1.SetTextFieldWidth(800);
         this.txt_cond1.SetTextFit(true);
         this.txt_cond2.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond2.SetTextColor(4467231);
         this.txt_cond2.SetTextSize(29);
         this.txt_cond2.SetTextFieldWidth(800);
         this.txt_cond2.SetTextFit(true);
         this.txt_cond3.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond3.SetTextColor(4467231);
         this.txt_cond3.SetTextSize(29);
         this.txt_cond3.SetTextFieldWidth(800);
         this.txt_cond3.SetTextFit(true);
      }
   }
}

