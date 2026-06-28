package start_memory_fla
{
   import flash.display.MovieClip;
   import script.icon_item.nut_icon_item;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   import script.xcp_frame1.smb_xcp_frame1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol46")]
   public dynamic class anm_condition01_23 extends MovieClip
   {
      
      public var all_lst:smb_xcp_frame1;
      
      public var dmy_item1:nut_tex00;
      
      public var dmy_item2:nut_tex00;
      
      public var dmy_item3:nut_tex00;
      
      public var mc_icon_item1:nut_icon_item;
      
      public var mc_icon_item2:nut_icon_item;
      
      public var mc_icon_item3:nut_icon_item;
      
      public var txt_cond1:smb_font;
      
      public var txt_cond2:smb_font;
      
      public var txt_cond3:smb_font;
      
      public var txt_cond_num1:smb_font;
      
      public var txt_cond_num2:smb_font;
      
      public var txt_cond_num3:smb_font;
      
      public var txt_cond_rew1:smb_font;
      
      public var txt_cond_rew2:smb_font;
      
      public var txt_cond_rew3:smb_font;
      
      public var txt_head:smb_font;
      
      public function anm_condition01_23()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
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
         this.txt_cond_rew1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond_rew1.SetTextSize(29);
         this.txt_cond_num1.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_cond_num1.SetTextSize(29);
         this.txt_cond2.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond2.SetTextColor(4467231);
         this.txt_cond2.SetTextSize(29);
         this.txt_cond2.SetTextFieldWidth(800);
         this.txt_cond2.SetTextFit(true);
         this.txt_cond_rew2.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond_rew2.SetTextSize(29);
         this.txt_cond_num2.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_cond_num2.SetTextSize(29);
         this.txt_cond3.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond3.SetTextColor(4467231);
         this.txt_cond3.SetTextSize(29);
         this.txt_cond3.SetTextFieldWidth(800);
         this.txt_cond3.SetTextFit(true);
         this.txt_cond_rew3.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond_rew3.SetTextSize(29);
         this.txt_cond_num3.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_cond_num3.SetTextSize(29);
      }
   }
}

