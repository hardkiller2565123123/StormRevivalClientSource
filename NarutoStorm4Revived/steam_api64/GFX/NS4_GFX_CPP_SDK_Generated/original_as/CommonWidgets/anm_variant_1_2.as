package stagesel_fla
{
   import flash.display.MovieClip;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursol_s;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol29")]
   public dynamic class anm_variant_1 extends MovieClip
   {
      
      public var mc_variant_b:MovieClip;
      
      public var txt_caution:smb_font;
      
      public var btn_l2:all_btn_plat;
      
      public var btn_r2:all_btn_plat;
      
      private var m_button_l2:MovieClip;
      
      private var m_button_r2:MovieClip;
      
      public var cursol_l:nut_cursol_s;
      
      public var cursol_r:nut_cursol_s;
      
      private var m_cursol_l:MovieClip;
      
      private var m_cursol_r:MovieClip;
      
      public function anm_variant_1()
      {
         super();
         this.m_button_l2 = this.getChildByName("btn_l2") as MovieClip;
         this.m_button_r2 = this.getChildByName("btn_r2") as MovieClip;
         this.m_cursol_l = this.getChildByName("cursol_l") as MovieClip;
         this.m_cursol_r = this.getChildByName("cursol_r") as MovieClip;
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         var _loc1_:all_btn_plat = this.getChildByName("btn_l2") as all_btn_plat;
         var _loc4_:all_btn_plat = this.getChildByName("btn_r2") as all_btn_plat;
         if(Boolean(_loc1_) && Boolean(_loc4_))
         {
            _loc1_.SetButtonId("btn_l2");
            _loc4_.SetButtonId("btn_r2");
         }
         this.txt_caution.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_caution.SetTextColor(16507777);
         this.txt_caution.SetTextSize(35);
      }
   }
}

