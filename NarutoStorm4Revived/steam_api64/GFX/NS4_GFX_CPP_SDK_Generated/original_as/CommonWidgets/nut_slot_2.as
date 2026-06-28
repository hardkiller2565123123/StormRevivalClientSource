package script.custom
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursor_m;
   import script.xcmn_menu.nut_frame_1;
   import script.xcp_numbg1.nut_numbg1_off;
   import script.xcp_numbg1.nut_numbg1_on;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public class nut_slot extends MovieClip
   {
      
      public var mc_cursor:nut_cursor_m;
      
      public var mc_kwrm:smb_kwrm_base;
      
      public var mc_num_base1:nut_numbg1_on;
      
      public var mc_num_base2:nut_numbg1_off;
      
      public var mc_off:MovieClip;
      
      public var mc_ougifin:smb_ougifin_base;
      
      public var mc_sel:nut_frame_1;
      
      public var mc_slot_base:MovieClip;
      
      public var txt_slot_num:smb_font;
      
      private var m_slotNoTextMC:smb_font;
      
      private var m_kawarimiInfoMC:smb_kwrm_base;
      
      private var m_ougiFinInfoMC:smb_ougifin_base;
      
      private var m_selIdx:int = -1;
      
      public function nut_slot()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         this.m_slotNoTextMC = this["txt_slot_num"];
         this.m_kawarimiInfoMC = this["mc_kwrm"];
         this.m_ougiFinInfoMC = this["mc_ougifin"];
         this.m_kawarimiInfoMC.SetEnable();
         this.m_ougiFinInfoMC.SetEnable();
      }
      
      public function Initialize(param1:Boolean, param2:Boolean, param3:Array) : *
      {
         if(param2)
         {
            this.m_kawarimiInfoMC.SetEnable();
         }
         else
         {
            this.m_kawarimiInfoMC.SetImpossible();
         }
         this.m_ougiFinInfoMC.LoadImgAll(param3);
      }
      
      public function SetSelect() : *
      {
         this.gotoAndStop("on");
      }
      
      public function SetEnable() : *
      {
         this.gotoAndStop("normal");
      }
      
      public function SetDisable() : *
      {
         this.gotoAndStop("off");
      }
      
      public function SetIndex(param1:int) : *
      {
         this.m_slotNoTextMC.SetText(param1.toString());
      }
      
      public function SetSelIndex(param1:int) : *
      {
         if(param1 == this.m_selIdx)
         {
            return;
         }
         switch(this.m_selIdx)
         {
            case define.CUSTOM_ITEM_KAWARIMI:
               this.m_kawarimiInfoMC.SetEnable();
               break;
            case define.CUSTOM_ITEM_OUGIFIN:
               this.m_ougiFinInfoMC.SetEnable();
         }
         switch(param1)
         {
            case define.CUSTOM_ITEM_KAWARIMI:
               this.m_kawarimiInfoMC.SetSelect();
               break;
            case define.CUSTOM_ITEM_OUGIFIN:
               this.m_ougiFinInfoMC.SetSelect();
         }
         this.m_selIdx = param1;
      }
      
      public function SetKawarimiIcon(param1:String) : *
      {
         this.m_kawarimiInfoMC.ChangeIcon(param1);
      }
      
      public function SetOugiFinishImg(param1:int) : *
      {
         this.m_ougiFinInfoMC.SetImg(param1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_slot_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slot_num.SetTextColor(16768125);
         this.txt_slot_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_slot_num.SetTextSize(30);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_slot_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slot_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_slot_num.SetTextSize(30);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_slot_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slot_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_slot_num.SetTextSize(30);
      }
   }
}

