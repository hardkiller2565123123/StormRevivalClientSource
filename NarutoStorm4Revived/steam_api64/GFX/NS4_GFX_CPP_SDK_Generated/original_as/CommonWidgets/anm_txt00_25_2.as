package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol48")]
   public dynamic class anm_txt00_25 extends MovieClip
   {
      
      public var txt_client:smb_font;
      
      public var txt_head00:smb_font;
      
      public var txt_head02:smb_font;
      
      public var txt_rew00:smb_font;
      
      public var txt_rew01:smb_font;
      
      public var txt_rew02:smb_font;
      
      public var txt_reward00:smb_font;
      
      public var txt_reward01:smb_font;
      
      public var txt_reward02:smb_font;
      
      public function anm_txt00_25()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_client.SetText("依頼者名_gy");
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_head00.SetTextSize(29);
         this.txt_head00.SetTextFieldWidth(800);
         this.txt_head00.SetTextFit(true);
         this.txt_client.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_client.SetTextColor(4467231);
         this.txt_client.SetTextSize(28);
         this.txt_client.SetTextFieldWidth(800);
         this.txt_client.SetTextFit(true);
         this.txt_head02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head02.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_head02.SetTextSize(29);
         this.txt_head02.SetTextFieldWidth(800);
         this.txt_head02.SetTextFit(true);
         this.txt_reward00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward00.SetTextSize(30);
         this.txt_reward01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward01.SetTextSize(30);
         this.txt_reward02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward02.SetTextSize(30);
         this.txt_rew00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew00.SetTextSize(30);
         this.txt_rew01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew01.SetTextSize(30);
         this.txt_rew02.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew02.SetTextSize(30);
      }
   }
}

