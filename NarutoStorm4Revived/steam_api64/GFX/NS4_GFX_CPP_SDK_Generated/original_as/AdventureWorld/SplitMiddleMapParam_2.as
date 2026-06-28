package script.map_sm
{
   import flash.geom.Point;
   import flash.utils.Dictionary;
   
   internal class SplitMiddleMapParam
   {
      
      public var m_leftTopPointList:Dictionary = new Dictionary();
      
      public var m_miniMapWidthList:Dictionary = new Dictionary();
      
      public var m_stageLeftTopPointList:Dictionary = new Dictionary();
      
      public var m_stageRightBottomPointList:Dictionary = new Dictionary();
      
      public var m_miniMapRotationList:Dictionary = new Dictionary();
      
      public var m_splitStageCodeList:Array = new Array();
      
      public var m_nowStageCode:String = "";
      
      public function SplitMiddleMapParam()
      {
         super();
         this.m_leftTopPointList["sa11a"] = new Point(444,816);
         this.m_leftTopPointList["sa11b"] = new Point(445,686);
         this.m_leftTopPointList["sa11c"] = new Point(448,545);
         this.m_leftTopPointList["sa11d"] = new Point(453,412);
         this.m_leftTopPointList["sa11e"] = new Point(400,468);
         this.m_leftTopPointList["sa11f"] = new Point(347,397);
         this.m_leftTopPointList["sa11g"] = new Point(448,292);
         this.m_leftTopPointList["sa11h"] = new Point(439,176);
         this.m_leftTopPointList["sa11i"] = new Point(427,59);
         this.m_leftTopPointList["sa11j"] = new Point(421,586);
         this.m_leftTopPointList["sa11k"] = new Point(502,302);
         this.m_leftTopPointList["sa16a"] = new Point(389,699);
         this.m_leftTopPointList["sa16b"] = new Point(459,622);
         this.m_leftTopPointList["sa16c"] = new Point(442,452);
         this.m_leftTopPointList["sa16d"] = new Point(430,211);
         this.m_leftTopPointList["sa16e"] = new Point(435,44);
         this.m_leftTopPointList["sa34a"] = new Point(539,787);
         this.m_leftTopPointList["sa34b"] = new Point(530,630);
         this.m_leftTopPointList["sa34d"] = new Point(232,524);
         this.m_leftTopPointList["sa34f"] = new Point(284,92);
         this.m_leftTopPointList["sa34g"] = new Point(468,84);
         this.m_leftTopPointList["sa34h"] = new Point(616,383);
         this.m_leftTopPointList["sa35a"] = new Point(263,334);
         this.m_leftTopPointList["sa02b"] = new Point(204,711);
         this.m_leftTopPointList["sa36a"] = new Point(609,655);
         this.m_leftTopPointList["sa36aaa"] = new Point(439,620);
         this.m_leftTopPointList["sa36b"] = new Point(246,416);
         this.m_leftTopPointList["sa36c"] = new Point(287,195);
         this.m_leftTopPointList["sa36d"] = new Point(323,93);
         this.m_leftTopPointList["sa36e"] = new Point(158,73);
         this.m_leftTopPointList["sa36cc"] = new Point(266,547);
         this.m_leftTopPointList["sa36f"] = new Point(112,145);
         this.m_leftTopPointList["sa70a"] = new Point(-33,-20);
         this.m_leftTopPointList["sa70b"] = new Point(132,310);
         this.m_leftTopPointList["sa70c"] = new Point(541,188);
         this.m_leftTopPointList["sa70d"] = new Point(676,89);
         this.m_leftTopPointList["sa70e"] = new Point(492,107);
         this.m_leftTopPointList["sa70f"] = new Point(456,736);
         this.m_leftTopPointList["sa70g"] = new Point(510,332);
         this.m_leftTopPointList["sa70h"] = new Point(514,290);
         this.m_leftTopPointList["sa70i"] = new Point(459,248);
         this.m_leftTopPointList["sa70k"] = new Point(204,401);
         this.m_stageLeftTopPointList["sa11a"] = new Point(-2205.052,1900.1217);
         this.m_stageLeftTopPointList["sa11b"] = new Point(-3886.083,3517.019);
         this.m_stageLeftTopPointList["sa11c"] = new Point(-2250.5715,2196.0645);
         this.m_stageLeftTopPointList["sa11d"] = new Point(-2975.463,3968.01);
         this.m_stageLeftTopPointList["sa11e"] = new Point(-793.439,841.608);
         this.m_stageLeftTopPointList["sa11f"] = new Point(-738.287,726.161);
         this.m_stageLeftTopPointList["sa11g"] = new Point(-2278.394,2594.917);
         this.m_stageLeftTopPointList["sa11h"] = new Point(-2329.913,2309.907);
         this.m_stageLeftTopPointList["sa11i"] = new Point(-1767.963,1253.482);
         this.m_stageLeftTopPointList["sa11j"] = new Point(-550,850);
         this.m_stageLeftTopPointList["sa11k"] = new Point(-650,500);
         this.m_stageLeftTopPointList["sa16a"] = new Point(-1500,1500);
         this.m_stageLeftTopPointList["sa16b"] = new Point(-1500,1000);
         this.m_stageLeftTopPointList["sa16c"] = new Point(-1150,1550);
         this.m_stageLeftTopPointList["sa16d"] = new Point(-2000,1800);
         this.m_stageLeftTopPointList["sa16e"] = new Point(-2000,1500);
         this.m_stageLeftTopPointList["sa34a"] = new Point(-4500,7800.00049);
         this.m_stageLeftTopPointList["sa34b"] = new Point(-5000,5500);
         this.m_stageLeftTopPointList["sa34d"] = new Point(-4750,5250);
         this.m_stageLeftTopPointList["sa34f"] = new Point(-5500,9700);
         this.m_stageLeftTopPointList["sa34g"] = new Point(-5400,5900);
         this.m_stageLeftTopPointList["sa34h"] = new Point(-4300,4300);
         this.m_stageLeftTopPointList["sa35a"] = new Point(-3375,3000);
         this.m_stageLeftTopPointList["sa02b"] = new Point(-3300,2700);
         this.m_stageLeftTopPointList["sa36a"] = new Point(5500,3200);
         this.m_stageLeftTopPointList["sa36aaa"] = new Point(-12200,2600);
         this.m_stageLeftTopPointList["sa36b"] = new Point(-3600,1800);
         this.m_stageLeftTopPointList["sa36c"] = new Point(-4000,7300);
         this.m_stageLeftTopPointList["sa36d"] = new Point(-4500,6000);
         this.m_stageLeftTopPointList["sa36e"] = new Point(-3500,4000);
         this.m_stageLeftTopPointList["sa36cc"] = new Point(-700,1000);
         this.m_stageLeftTopPointList["sa36f"] = new Point(-600,600);
         this.m_stageLeftTopPointList["sa70a"] = new Point(-30000,54000);
         this.m_stageLeftTopPointList["sa70b"] = new Point(-12000,22000);
         this.m_stageLeftTopPointList["sa70c"] = new Point(-14500,24500);
         this.m_stageLeftTopPointList["sa70d"] = new Point(-6000,7000);
         this.m_stageLeftTopPointList["sa70e"] = new Point(-1000,1000);
         this.m_stageLeftTopPointList["sa70f"] = new Point(-750,750);
         this.m_stageLeftTopPointList["sa70g"] = new Point(-750,400);
         this.m_stageLeftTopPointList["sa70h"] = new Point(-750,750);
         this.m_stageLeftTopPointList["sa70i"] = new Point(-850,750);
         this.m_stageLeftTopPointList["sa70k"] = new Point(-750,750);
         this.m_stageRightBottomPointList["sa11a"] = new Point(3410.5934,-4775.8416);
         this.m_stageRightBottomPointList["sa11b"] = new Point(4243.353,-4614.723);
         this.m_stageRightBottomPointList["sa11c"] = new Point(2151.1725,-2206.9275);
         this.m_stageRightBottomPointList["sa11d"] = new Point(3823.4997,-2832.882);
         this.m_stageRightBottomPointList["sa11e"] = new Point(866.373,-818.674);
         this.m_stageRightBottomPointList["sa11f"] = new Point(769.286,-781.839);
         this.m_stageRightBottomPointList["sa11g"] = new Point(2781.96,-2466.873);
         this.m_stageRightBottomPointList["sa11h"] = new Point(348,-2432.36);
         this.m_stageRightBottomPointList["sa11i"] = new Point(1677.574,-2193.034);
         this.m_stageRightBottomPointList["sa11j"] = new Point(950,-650);
         this.m_stageRightBottomPointList["sa11k"] = new Point(350,-500);
         this.m_stageRightBottomPointList["sa16a"] = new Point(1500,-1500);
         this.m_stageRightBottomPointList["sa16b"] = new Point(2500,-3000);
         this.m_stageRightBottomPointList["sa16c"] = new Point(2350,-1950);
         this.m_stageRightBottomPointList["sa16d"] = new Point(2000,-2200);
         this.m_stageRightBottomPointList["sa16e"] = new Point(2000,-2500);
         this.m_stageRightBottomPointList["sa34a"] = new Point(4500,-1200);
         this.m_stageRightBottomPointList["sa34b"] = new Point(5000,-4500);
         this.m_stageRightBottomPointList["sa34d"] = new Point(750,-250);
         this.m_stageRightBottomPointList["sa34f"] = new Point(9500,-5300);
         this.m_stageRightBottomPointList["sa34g"] = new Point(4600,-4100);
         this.m_stageRightBottomPointList["sa34h"] = new Point(3700,-3700);
         this.m_stageRightBottomPointList["sa35a"] = new Point(2625,-3000);
         this.m_stageRightBottomPointList["sa02b"] = new Point(2700,-3300);
         this.m_stageRightBottomPointList["sa36a"] = new Point(12500,-3800);
         this.m_stageRightBottomPointList["sa36aaa"] = new Point(-6200,-3400);
         this.m_stageRightBottomPointList["sa36b"] = new Point(2400,-4200);
         this.m_stageRightBottomPointList["sa36c"] = new Point(5000,-1700);
         this.m_stageRightBottomPointList["sa36d"] = new Point(4500,-2991);
         this.m_stageRightBottomPointList["sa36e"] = new Point(3500,-3000);
         this.m_stageRightBottomPointList["sa36cc"] = new Point(1300,-1000);
         this.m_stageRightBottomPointList["sa36f"] = new Point(600,-600);
         this.m_stageRightBottomPointList["sa70a"] = new Point(30000,-6000);
         this.m_stageRightBottomPointList["sa70b"] = new Point(18000,-8000);
         this.m_stageRightBottomPointList["sa70c"] = new Point(20500,-10500);
         this.m_stageRightBottomPointList["sa70d"] = new Point(6000,-5000);
         this.m_stageRightBottomPointList["sa70e"] = new Point(1000,-1000);
         this.m_stageRightBottomPointList["sa70f"] = new Point(750,-750);
         this.m_stageRightBottomPointList["sa70g"] = new Point(750,-1100);
         this.m_stageRightBottomPointList["sa70h"] = new Point(750,-750);
         this.m_stageRightBottomPointList["sa70i"] = new Point(750,-750);
         this.m_stageRightBottomPointList["sa70k"] = new Point(750,-750);
         this.m_miniMapRotationList["sa35a"] = 90 * Math.PI / 180;
         this.m_miniMapRotationList["sa02b"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa02b"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa36a"] = 30 * Math.PI / 180;
         this.m_miniMapRotationList["sa36d"] = 3.392 * Math.PI / 180;
         this.m_miniMapRotationList["sa36e"] = 8.035 * Math.PI / 180;
         this.m_miniMapRotationList["sa36f"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa16a"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa16b"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa16c"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa16d"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa16e"] = 180 * Math.PI / 180;
         this.m_miniMapRotationList["sa11i"] = 180 * Math.PI / 180;
         this.m_miniMapWidthList["sa11a"] = 157;
         this.m_miniMapWidthList["sa11b"] = 157;
         this.m_miniMapWidthList["sa11c"] = 157;
         this.m_miniMapWidthList["sa11d"] = 157;
         this.m_miniMapWidthList["sa11e"] = 157;
         this.m_miniMapWidthList["sa11f"] = 157;
         this.m_miniMapWidthList["sa11g"] = 157;
         this.m_miniMapWidthList["sa11h"] = 157;
         this.m_miniMapWidthList["sa11i"] = 157;
         this.m_miniMapWidthList["sa11j"] = 87;
         this.m_miniMapWidthList["sa11k"] = 187;
         this.m_miniMapWidthList["map_sa34"] = 233;
         this.m_miniMapWidthList["map_sa35a"] = 233;
         this.m_miniMapWidthList["sa70a"] = 1095;
         this.m_miniMapWidthList["sa70b"] = 329;
         this.m_miniMapWidthList["sa70c"] = 289;
         this.m_miniMapWidthList["sa70d"] = 159;
         this.m_miniMapWidthList["sa70e"] = 55;
         this.m_miniMapWidthList["sa70f"] = 65;
         this.m_miniMapWidthList["sa70g"] = 57;
         this.m_miniMapWidthList["sa70h"] = 46;
         this.m_miniMapWidthList["sa70i"] = 66;
         this.m_miniMapWidthList["sa70k"] = 49;
         this.m_miniMapWidthList["sa36aaa"] = 332;
         this.m_miniMapWidthList["sa36a"] = 332;
         this.m_miniMapWidthList["sa36b"] = 408;
         this.m_miniMapWidthList["sa36c"] = 269;
         this.m_miniMapWidthList["sa36d"] = 188;
         this.m_miniMapWidthList["sa36e"] = 188;
         this.m_miniMapWidthList["sa36cc"] = 113;
         this.m_miniMapWidthList["sa36f"] = 124;
         this.m_miniMapWidthList["map_sa16"] = 268;
         this.m_splitStageCodeList.push("sa11");
         this.m_splitStageCodeList.push("sa16");
         this.m_splitStageCodeList.push("sa34");
         this.m_splitStageCodeList.push("sa35a");
         this.m_splitStageCodeList.push("sa02b");
         this.m_splitStageCodeList.push("sa36");
         this.m_splitStageCodeList.push("sa70");
      }
      
      public function IsSplitStage(param1:String) : Boolean
      {
         var _loc2_:Boolean = false;
         var _loc3_:int = 0;
         while(_loc3_ < this.m_splitStageCodeList.length)
         {
            if(param1.indexOf(this.m_splitStageCodeList[_loc3_]) != -1)
            {
               _loc2_ = true;
               break;
            }
            _loc3_++;
         }
         return _loc2_;
      }
      
      public function SetStageCode(param1:String) : *
      {
         trace("SetStageCode:" + param1);
         this.m_nowStageCode = param1;
      }
      
      public function GetMiniMapOffset() : Point
      {
         var _loc1_:Point = null;
         if(this.m_leftTopPointList.hasOwnProperty(this.m_nowStageCode) == true)
         {
            _loc1_ = this.m_leftTopPointList[this.m_nowStageCode];
         }
         return _loc1_;
      }
   }
}

