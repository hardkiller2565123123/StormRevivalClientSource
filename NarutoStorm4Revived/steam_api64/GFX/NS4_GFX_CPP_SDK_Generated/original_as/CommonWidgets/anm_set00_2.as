package script.preset
{
   import ELoader.ExtendLoader;
   import Struct.MessageParam;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   import script.charicon_s.nut_charicon_s;
   import script.charicon_s.nut_frame_p;
   import script.charsel.*;
   import script.infoData.SlotData;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_frame_1;
   import script.xcmn_menu.nut_frame_2;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class anm_set00 extends MovieClip
   {
      
      public var all_charicon_frame02:nut_frame_p;
      
      public var all_charicon_s02:nut_charicon_s;
      
      public var txt_no:smb_font;
      
      public var dmy_asst1:nut_tex00;
      
      public var all_charicon_s00:nut_charicon_s;
      
      public var mc_slot_index:MovieClip;
      
      public var mc_combo3:anm_combo;
      
      public var all_charicon_s01:nut_charicon_s;
      
      public var all_charicon_frame01:nut_frame_p;
      
      public var mc_frame_red:nut_frame_1;
      
      public var mc_combo2:anm_combo;
      
      public var mc_combo1:anm_combo;
      
      public var mc_set_base:MovieClip;
      
      public var mc_slot_bg:MovieClip;
      
      public var dmy_asst2:nut_tex00;
      
      public var txt_none:smb_font;
      
      public var mc_frame_blue:nut_frame_2;
      
      public var dmy_asst3:nut_tex00;
      
      private const CCD_TEAM_MAX_NUM:* = 3;
      
      private var m_redFrameMC:MovieClip;
      
      private var m_blueFrameMC:MovieClip;
      
      private var m_leaderIconMC:nut_charicon_s;
      
      private var m_support1IconMC:nut_charicon_s;
      
      private var m_support2IconMC:nut_charicon_s;
      
      private var m_slotData:SlotData;
      
      private var m_leaderActLoader:Array;
      
      private var m_supportLActLoader:Array;
      
      private var m_supportRActLoader:Array;
      
      private var m_comboIcon:Array;
      
      public function anm_set00()
      {
         var _loc2_:URLRequest = null;
         this.m_leaderActLoader = new Array(CharselParam.CCD_SUPPORT_ACTION_NUM);
         this.m_supportLActLoader = new Array(CharselParam.CCD_SUPPORT_ACTION_NUM);
         this.m_supportRActLoader = new Array(CharselParam.CCD_SUPPORT_ACTION_NUM);
         this.m_comboIcon = new Array(this.CCD_TEAM_MAX_NUM);
         super();
         addFrameScript(0,this.frame1,3,this.frame4);
         this.m_redFrameMC = this["mc_frame_red"];
         this.m_blueFrameMC = this["mc_frame_blue"];
         var _loc1_:int = 0;
         _loc1_ = 0;
         while(_loc1_ < CharselParam.CCD_SUPPORT_ACTION_NUM)
         {
            _loc2_ = new URLRequest(CharselParam.CCD_SUPPORT_ACTION_ICON_TBL[_loc1_]);
            this.m_leaderActLoader[_loc1_] = new ExtendLoader();
            this.m_leaderActLoader[_loc1_].load(_loc2_);
            this.m_leaderActLoader[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            this.dmy_asst1.addChild(this.m_leaderActLoader[_loc1_]);
            this.m_supportLActLoader[_loc1_] = new ExtendLoader();
            this.m_supportLActLoader[_loc1_].load(_loc2_);
            this.m_supportLActLoader[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            this.dmy_asst2.addChild(this.m_supportLActLoader[_loc1_]);
            this.m_supportRActLoader[_loc1_] = new ExtendLoader();
            this.m_supportRActLoader[_loc1_].load(_loc2_);
            this.m_supportRActLoader[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            this.dmy_asst3.addChild(this.m_supportRActLoader[_loc1_]);
            _loc1_++;
         }
         this.SetAssistType(0,false,0);
         this.SetAssistType(1,false,0);
         this.SetAssistType(2,false,0);
         this.m_comboIcon[0] = MovieClip(this["mc_combo1"]);
         this.m_comboIcon[1] = MovieClip(this["mc_combo2"]);
         this.m_comboIcon[2] = MovieClip(this["mc_combo3"]);
         _loc1_ = 0;
         while(_loc1_ < this.CCD_TEAM_MAX_NUM)
         {
            if(this.m_comboIcon[_loc1_])
            {
               this.m_comboIcon[_loc1_].visible = false;
            }
            _loc1_++;
         }
      }
      
      public function GetSlotData() : SlotData
      {
         return this.m_slotData;
      }
      
      public function SetIndexNumber(param1:int) : *
      {
         var _loc2_:smb_font = this["txt_no"];
         _loc2_.SetText(param1.toString());
      }
      
      public function SetSlotData(param1:SlotData) : *
      {
         trace("anm_set00::SetSlotData()");
         trace("leader = " + param1.m_leaderId);
         this.m_slotData = param1;
         if(this.m_slotData.m_leaderId == null)
         {
            this.SetNoneMC();
         }
         else if(this.m_slotData.m_support1Id != null && this.m_slotData.m_support2Id != null)
         {
            this.SetThreeTeamMC();
         }
         else if(this.m_slotData.m_support1Id != null)
         {
            this.SetTwoTeamMC();
         }
         else
         {
            this.SetSingleTeamMC();
         }
      }
      
      public function SetNoneMC() : *
      {
         this.gotoAndStop("none");
         var _loc1_:smb_font = this["txt_none"];
         var _loc2_:MessageParam = MessageParam(ExternalInterface.call("MessageConvertParam","battle_preset_014"));
         _loc1_.SetText(_loc2_.m_cmd);
         _loc1_.visible = true;
      }
      
      public function SetSingleTeamMC() : *
      {
         this.gotoAndStop("single");
         this.m_leaderIconMC = this["all_charicon_s00"];
         this.SetLeaderIcon(this.m_slotData.m_leaderId,this.m_slotData.m_leaderType);
      }
      
      public function SetTwoTeamMC() : *
      {
         this.gotoAndStop("two");
         this.m_leaderIconMC = this["all_charicon_s00"];
         this.m_support1IconMC = this["all_charicon_s01"];
         this.SetLeaderIcon(this.m_slotData.m_leaderId,this.m_slotData.m_leaderType);
         this.SetSupport1Icon(this.m_slotData.m_support1Id,this.m_slotData.m_support1Type);
      }
      
      public function SetThreeTeamMC() : *
      {
         this.gotoAndStop("three");
         this.m_leaderIconMC = this["all_charicon_s00"];
         this.m_support1IconMC = this["all_charicon_s01"];
         this.m_support2IconMC = this["all_charicon_s02"];
         this.SetLeaderIcon(this.m_slotData.m_leaderId,this.m_slotData.m_leaderType);
         this.SetSupport1Icon(this.m_slotData.m_support1Id,this.m_slotData.m_support1Type);
         this.SetSupport2Icon(this.m_slotData.m_support2Id,this.m_slotData.m_support2Type);
      }
      
      public function SetLeaderIcon(param1:String, param2:int) : *
      {
         this.m_slotData.m_leaderId = param1;
         this.m_leaderIconMC.SetCharaCode(param1);
         this.m_slotData.m_leaderType = param2;
         var _loc3_:Boolean = true;
         if(param1 == "brank_oth")
         {
            _loc3_ = false;
         }
         this.SetAssistType(0,_loc3_,this.m_slotData.m_leaderType);
         var _loc4_:smb_font = this["txt_none"];
         _loc4_.visible = false;
      }
      
      public function SetSupport1Icon(param1:String, param2:int) : *
      {
         this.m_slotData.m_support1Id = param1;
         this.m_support1IconMC.SetCharaCode(param1);
         this.m_slotData.m_support1Type = param2;
         var _loc3_:Boolean = true;
         if(param1 == "brank_oth")
         {
            _loc3_ = false;
         }
         this.SetAssistType(1,_loc3_,this.m_slotData.m_support1Type);
      }
      
      public function SetSupport2Icon(param1:String, param2:int) : *
      {
         this.m_slotData.m_support2Id = param1;
         this.m_support2IconMC.SetCharaCode(param1);
         this.m_slotData.m_support2Type = param2;
         var _loc3_:Boolean = true;
         if(param1 == "brank_oth")
         {
            _loc3_ = false;
         }
         this.SetAssistType(2,_loc3_,this.m_slotData.m_support2Type);
      }
      
      public function SetComboIcon(param1:Boolean, param2:Boolean, param3:Boolean) : *
      {
         if(this.m_comboIcon[0])
         {
            this.m_comboIcon[0].visible = param1;
         }
         if(this.m_comboIcon[1])
         {
            this.m_comboIcon[1].visible = param2;
         }
         if(this.m_comboIcon[2])
         {
            this.m_comboIcon[2].visible = param3;
         }
      }
      
      public function SetCursorSelect() : *
      {
         this.m_redFrameMC.visible = false;
         this.m_blueFrameMC.visible = true;
      }
      
      public function SetCursorOn() : *
      {
         this.m_redFrameMC.visible = true;
         this.m_blueFrameMC.visible = false;
      }
      
      public function SetCursorOff() : *
      {
         this.m_redFrameMC.visible = false;
         this.m_blueFrameMC.visible = false;
      }
      
      public function IsEnableReset() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_slotData.m_leaderId != null)
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function Reset() : *
      {
         this.SetNoneMC();
         this.m_slotData.Reset();
      }
      
      public function SetAssistType(param1:int, param2:Boolean, param3:int) : *
      {
         var _loc5_:int = 0;
         var _loc4_:Array = null;
         switch(param1)
         {
            case 0:
               _loc4_ = this.m_leaderActLoader;
               break;
            case 1:
               _loc4_ = this.m_supportLActLoader;
               break;
            case 2:
               _loc4_ = this.m_supportRActLoader;
         }
         if(_loc4_)
         {
            _loc5_ = 0;
            while(_loc5_ < CharselParam.CCD_SUPPORT_ACTION_NUM)
            {
               DisplayObject(_loc4_[_loc5_]).visible = false;
               _loc5_++;
            }
            if(param2)
            {
               DisplayObject(_loc4_[param3]).visible = true;
            }
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_no.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_no.SetTextSize(28);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_none.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_no.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
   }
}

